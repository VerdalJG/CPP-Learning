#include "TanksManager.h"

#include <windows.h>
#include "Direction.h"
#include "Map.h"
#include "Bullet.h"
#include "TankInfo.h"

const char* CTanksManager::s_sAsciiTank[] =
{
	// Up
	"   _^_ \n|___|\n[ooo]\n",
	// Down
	"   ___ \n|_O_|\n[ooo]\n",
	// Left
	"    __ \n=|__|\n[ooo]\n",
	// Right
	"   __  \n|__|=\n[ooo]\n",
};
const size_t CTanksManager::s_uAsciiTankSize = sizeof(CTanksManager::s_sAsciiTank) / sizeof(const char*);
static_assert(CTanksManager::s_uAsciiTankSize == static_cast<size_t>(EDirection::Count));

const char* CTanksManager::s_sAsciiTankShooting[] =
{
	// Up
	u8"   _█_ \n|___|\n[ooo]\n",
	// Down
	u8"   ___ \n|_█_|\n[ooo]\n",
	// Left
	u8"    __ \n█|__|\n[ooo]\n",
	// Right
	u8"   __  \n|__|█\n[ooo]\n",
};
const size_t CTanksManager::s_uAsciiTankShootingSize = sizeof(CTanksManager::s_sAsciiTankShooting) / sizeof(const char*);
static_assert(CTanksManager::s_uAsciiTankShootingSize == static_cast<size_t>(EDirection::Count));

const char* CTanksManager::s_sAsciiTankExploding[] =
{
	// Ka...
	" ___ \n|___|\n[ooo]\n",
	// Boom
	u8"█████\n█████\n█████\n",
	// Dead
	"     \n     \n     \n",
};
const size_t CTanksManager::s_uAsciiTankExplodingSize = sizeof(CTanksManager::s_sAsciiTankExploding) / sizeof(const char*);

const char* CTanksManager::s_sAsciiBullet[] =
{
		"^", // Up
		"v", // Down
		"<", // Left
		">" // Right
};
const size_t CTanksManager::s_uAsciiBulletSize = sizeof(CTanksManager::s_sAsciiBullet) / sizeof(const char*);
static_assert(CTanksManager::s_uAsciiBulletSize == static_cast<size_t>(EDirection::Count));

CTanksManager::~CTanksManager()
{
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		delete pTankInfo->pTank;
		if (pTankInfo->pBullet)
		{
			delete pTankInfo->pBullet;
		}
		delete pTankInfo;
	}
}

void CTanksManager::Update()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CTanksManager::Render(0, 0, CTanksManager::GetInstance().GetMap().GetAscii().c_str());

	// First update the exploding tanks to draw in the back
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		// Tank exploding (update)
		if (pTankInfo->bExploding)
		{
			pTankInfo->pTank->UpdateExploding();
		}
	}

	std::vector<CTank*> tTanksThatShootThisTick;

	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
  	// Tank exploding (skip)
		if (pTankInfo->bExploding)
		{
			continue;
		}

		pTankInfo->pTank->eDesiredAction = EAction::None;
		// Update tank
		pTankInfo->pTank->Update();

		// Shooting?
		if (pTankInfo->pTank->eDesiredAction == EAction::Shoot)
		{
			TryFireBullet(pTankInfo);
			tTanksThatShootThisTick.push_back(pTankInfo->pTank);
		}
		// Move?
		else if (pTankInfo->pTank->eDesiredAction == EAction::Move)
		{
			CTanksManager::GetInstance().TryMoveTank(pTankInfo->pTank);
		}

		// Draw tank
		pTankInfo->pTank->Draw();
	}

	// Do CTanksManager::s_iBulletSpeed to allow the bullet ccd
	for (int iBulletIter = 0; iBulletIter < CTanksManager::s_iBulletSpeed; ++iBulletIter)
	{
		for (CTankInfo* pTankInfo : m_tTankInfos)
		{
			if (pTankInfo->pBullet)
			{
				bool const bShootedThisTick(std::find(tTanksThatShootThisTick.begin(), tTanksThatShootThisTick.end(), pTankInfo->pTank) == tTanksThatShootThisTick.end());
				UpdateBullet(pTankInfo, bShootedThisTick);
			}
		}
	}

	CTanksManager::GetInstance().RemoveDeadTanks();

	// Health info
	SHORT iTankIndex = 0;
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		SetConsoleTextAttribute(hConsole, pTankInfo->pTank->GetColor());

		COORD oCoord = { 3, 28 + iTankIndex };
		SetConsoleCursorPosition(hConsole, oCoord);
		printf("%s", pTankInfo->pTank->GetName().c_str());

		oCoord.X = 23;
		SetConsoleCursorPosition(hConsole, oCoord);
		if (pTankInfo->pTank->IsDead())
		{
			printf("DEAD");
		}
		else
		{
			printf("%d HP (%d, %d)", pTankInfo->pTank->GetHealth(), pTankInfo->pTank->GetPosX(), pTankInfo->pTank->GetPosY());
		}

		SetConsoleTextAttribute(hConsole, 15);

		++iTankIndex;
	}
}

void CTanksManager::AddTank(CTank* _pTank)
{
	if (std::find(m_tAllTanks.begin(), m_tAllTanks.end(), _pTank) == m_tAllTanks.end())
	{
		m_tAllTanks.push_back(_pTank);
		m_tTanks.push_back(_pTank);

		// Create tank position
		m_tTankInfos.push_back(new CTankInfo());
		CTankInfo* pTankPos(m_tTankInfos[m_tTankInfos.size() - 1]);
		pTankPos->pTank = _pTank;
		pTankPos->iX = _pTank->GetPosInitialX();
		pTankPos->iY = _pTank->GetPosInitialY();
		pTankPos->iHealth = CTanksManager::s_iInitialTankHealth;
		_pTank->SetTankInfoRef(pTankPos);
	}
}

void CTanksManager::SetTankInfo(CTank* _pTank, int _iX, int _iY)
{
	for(CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (pTankInfo->pTank == _pTank)
		{
			pTankInfo->iX = _iX;
			pTankInfo->iY = _iY;
			break;
		}
	}
}

void CTanksManager::TryMoveTank(CTank* _pTank)
{
	auto lambdaMoveCheck = [this](CTank* _pMovingTank, int X, int Y)
	{
		for (const CTank* pTank : m_tTanks)
		{
			if (pTank == _pMovingTank)
			{
				continue;
			}
			if (abs(pTank->GetPosX() - X) <= 4 && abs(pTank->GetPosY() - Y) <= 2)
			{
				return false; // collision with another tank
			}
		}
		if (!m_oMap.MoveCheck(_pMovingTank, X, Y))
		{
			return false;
		}
		return true;
	};

	int iX, iY;
	_pTank->GetPos(iX, iY);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	auto lambdaWriteBlankSpace = [&hConsole](SHORT _iX, SHORT _iY)
	{
		COORD oCoord = { _iX, _iY };
		SetConsoleCursorPosition(hConsole, oCoord);
		printf(" ");
	};

	if (_pTank->eDesiredAction == EAction::Move)
	{
		lambdaWriteBlankSpace(iX - 3, iY - 1);
		lambdaWriteBlankSpace(iX - 3, iY);
		lambdaWriteBlankSpace(iX - 3, iY + 1);

		lambdaWriteBlankSpace(iX - 2, iY - 1);
		lambdaWriteBlankSpace(iX - 2, iY);
		lambdaWriteBlankSpace(iX - 2, iY + 1);

		lambdaWriteBlankSpace(iX - 1, iY - 1);
		lambdaWriteBlankSpace(iX - 1, iY);
		lambdaWriteBlankSpace(iX - 1, iY + 1);

		lambdaWriteBlankSpace(iX, iY - 1);
		lambdaWriteBlankSpace(iX, iY);
		lambdaWriteBlankSpace(iX, iY + 1);

		lambdaWriteBlankSpace(iX + 1, iY - 1);
		lambdaWriteBlankSpace(iX + 1, iY);
		lambdaWriteBlankSpace(iX + 1, iY + 1);

		lambdaWriteBlankSpace(iX + 2, iY - 1);
		lambdaWriteBlankSpace(iX + 2, iY);
		lambdaWriteBlankSpace(iX + 2, iY + 1);

		lambdaWriteBlankSpace(iX + 3, iY - 1);
		lambdaWriteBlankSpace(iX + 3, iY);
		lambdaWriteBlankSpace(iX + 3, iY + 1);
		

		switch (_pTank->eDesiredLookDirection)
		{
		case EDirection::Up:
			if (lambdaMoveCheck(_pTank, iX, iY - 1))
			{
				SetTankInfo(_pTank, iX, iY - 1);
			}
			break;
		case EDirection::Down:
			if (lambdaMoveCheck(_pTank, iX, iY + 1))
			{
				SetTankInfo(_pTank, iX, iY + 1);
			}
			break;
		case EDirection::Left:
			if (lambdaMoveCheck(_pTank, iX - 1, iY))
			{
				SetTankInfo(_pTank, iX - 1, iY);
			}
			break;
		case EDirection::Right:
			if (lambdaMoveCheck(_pTank, iX + 1, iY))
			{
				SetTankInfo(_pTank, iX + 1, iY);
			}
			break;
		}
	}
}

bool CTanksManager::TryFireBullet(CTankInfo* _pTankInfo)
{
	if (_pTankInfo->pBullet == nullptr)
	{
		int iWidthCheck = CTanksManager::s_iTankWidth / 2;
		++iWidthCheck;
		int iHeightCheck = CTanksManager::s_iTankHeight / 2;
		++iHeightCheck;

		EDirection eDirection(_pTankInfo->pTank->eDesiredLookDirection);

		_pTankInfo->pBullet = new CBullet();
		_pTankInfo->pBullet->iX = eDirection == EDirection::Left ? _pTankInfo->iX - iWidthCheck : (eDirection == EDirection::Right ? _pTankInfo->iX + iWidthCheck : _pTankInfo->iX);
		_pTankInfo->pBullet->iY = eDirection == EDirection::Up ? _pTankInfo->iY - iHeightCheck : (eDirection == EDirection::Down ? _pTankInfo->iY + iHeightCheck : _pTankInfo->iY);
		_pTankInfo->pBullet->eDirection = eDirection;
	}
	return false;
}

void CTanksManager::ProcessTankImpact(const CTank* _pTank)
{
	if (CTanksManager::GetInstance().IsGameFinished() || _pTank->IsDead())
	{
		return;
	}

	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (pTankInfo->pTank == _pTank)
		{
			if (pTankInfo->iHealth > 0)
			{
				--pTankInfo->iHealth;

				if (pTankInfo->pTank->IsDead())
				{
					pTankInfo->bExploding = true;
				}
			}

			break;
		}
	}
}

void CTanksManager::UpdateBullet(CTankInfo* _pTankInfo, bool _bAllowMovement)
{
	if (_pTankInfo->pBullet)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, _pTankInfo->pTank->GetColor());

		COORD oCoord = { _pTankInfo->pBullet->iX, _pTankInfo->pBullet->iY };
		SetConsoleCursorPosition(hConsole, oCoord);

		printf(" ");
		if (_bAllowMovement)
		{
			switch (_pTankInfo->pBullet->eDirection)
			{
			case EDirection::Up: _pTankInfo->pBullet->iY--; break;
			case EDirection::Down: _pTankInfo->pBullet->iY++; break;
			case EDirection::Left: _pTankInfo->pBullet->iX--; break;
			case EDirection::Right: _pTankInfo->pBullet->iX++; break;
			}
		}

		COORD oNewCoord = { _pTankInfo->pBullet->iX, _pTankInfo->pBullet->iY };
		SetConsoleCursorPosition(hConsole, oNewCoord);

		const CTank* pCollisionTank = nullptr;
		bool bCollision = _pTankInfo->pBullet->CollisionCheck(pCollisionTank);
		printf(bCollision ? u8"█" : CTanksManager::s_sAsciiBullet[static_cast<int>(_pTankInfo->pBullet->eDirection)]);
		if (bCollision)
		{
			if (pCollisionTank)
			{
				ProcessTankImpact(pCollisionTank);
			}
			delete _pTankInfo->pBullet;
			_pTankInfo->pBullet = nullptr;
		}

		SetConsoleTextAttribute(hConsole, 15);
	}
}

void CTanksManager::RemoveDeadTanks()
{
	m_tTanks.remove_if([](const CTank* _pTank)
	{
		return _pTank->ToBeRemoved();
	});
}

bool CTanksManager::IsGameFinished() const
{
	int iNumAlive(0);
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (!pTankInfo->bExploding && !pTankInfo->pTank->IsExploding() && !pTankInfo->pTank->ToBeRemoved())
		{
			iNumAlive++;
		}
	}
	return iNumAlive <= 1;
}

void CTanksManager::Render(short _iX, short _iY, const char* _sString, int _iColor, bool _bDrawBlankSpaces)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, _iColor);

	COORD oInitialCoord = { _iX, _iY };
	SetConsoleCursorPosition(hConsole, oInitialCoord);

	const size_t uLength(strlen(_sString));
	short iCurrentX = _iX;
	short iCurrentY = _iY;
	for (unsigned int i = 0; i < uLength; ++i)
	{
		if (_sString[i] == '\n')
		{
			iCurrentX = _iX;
			++iCurrentY;
			COORD oCoord = { iCurrentX, iCurrentY };
			SetConsoleCursorPosition(hConsole, oCoord);
		}
		else
		{
			if (_sString[i] == ' ' && !_bDrawBlankSpaces)
			{
				COORD oCoord = { iCurrentX-1, iCurrentY };
				SetConsoleCursorPosition(hConsole, oCoord);
			}
			else
			{
				printf("%c", _sString[i]);
			}
			iCurrentX++;
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}
