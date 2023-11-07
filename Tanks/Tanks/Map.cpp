#include "Map.h"

#include "TanksManager.h"
#include "Bullet.h"

CMap::CMap()
{
	m_sAscii = std::string("") +
		u8"╔═════════════════════════════════════════════════════════════════════════╗" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"║                                                                         ║" + "\n" +
		u8"╚═════════════════════════════════════════════════════════════════════════╝" + "\n";
}

const std::string& CMap::GetAscii()  const
{
	return m_sAscii;
}

int CMap::GetHeight() const
{
	return 27;
}

int CMap::GetWidth() const
{
	return 74;
}

bool CMap::IsWall(int X, int Y) const
{
	if (X <= 0 || X >= GetWidth() || Y <= 0 || Y >= GetHeight())
	{
		return true;
	}
	return false;
}

bool CMap::MoveCheck(CTank* _pMovingTank, int X, int Y) const
{
	int iWidthCheck = CTanksManager::s_iTankWidth / 2;
	++iWidthCheck;
	int iHeightCheck = CTanksManager::s_iTankHeight / 2;
	++iHeightCheck;

	if (X < iWidthCheck || X >(GetWidth() - iWidthCheck) || Y < iHeightCheck || Y >(GetHeight() - iHeightCheck))
	{
		return false; // collision with border walls
	}

	return true;
}

bool CMap::CheckBulletCollision(CBullet* bullet) const
{
	return IsWall(bullet->iX, bullet->iY);
}
