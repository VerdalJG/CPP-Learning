#include "VFCTank.h"
#include "../TanksManager.h"
#include <vector>
#include "../Bullet.h"


VFCTank::VFCTank(int _iX, int _iY, int _iColor)
	: CTank("Vicente", _iX, _iY, _iColor)
{
} 

void VFCTank::Update()
{
	eDesiredAction = EAction::None;

	const CTank* pTarget(nullptr);
	const CBullet* bullet(nullptr);
	for (const CTank* pTank : CTanksManager::GetInstance().GetTanks())
	{
		if (pTank != this)
		{
			pTarget = pTank;
			bullet = pTarget->GetBullet();
			break;
		}
	}

	if (GetBullet() == nullptr)
	{
		int targetX = pTarget->GetPosX();
		int targetY = pTarget->GetPosY();
		if (std::abs(GetPosX() - targetX) < 5)
		{
			if (GetPosY() > targetY)// I am below
			{
				eDesiredLookDirection = EDirection::Up;
			}
			else
			{
				eDesiredLookDirection = EDirection::Down;
			}
			if (std::abs(GetPosY() - targetY) < 10)
			{
				eDesiredAction = EAction::Shoot;
			}
			else
			{
				eDesiredAction = EAction::Shoot;
			}
			
		}
		else if (std::abs(GetPosY() - targetY) < 2) // Same height - ish
		{
			if (GetPosX() > targetX)
			{
				eDesiredLookDirection = EDirection::Left;
			}
			else
			{
				eDesiredLookDirection = EDirection::Right;
					
			}
			if (std::abs(GetPosX() - targetX) < 10)
			{
				eDesiredAction = EAction::Shoot;
			}
			else
			{
				eDesiredAction = EAction::Shoot;
			}
		}
		else
		{
			if (std::abs(GetPosY() - targetY) < std::abs(GetPosX() - targetX))
			{
				if (GetPosY() < targetY)
				{
					eDesiredLookDirection = EDirection::Down;
				}
				else
				{
					eDesiredLookDirection = EDirection::Up;
				}
				eDesiredAction = EAction::Move;
			}
			else
			{
				if (GetPosX() < targetX)
				{
					eDesiredLookDirection = EDirection::Right;
				}
				else
				{
					eDesiredLookDirection = EDirection::Left;
				}
				eDesiredAction = EAction::Move;
			}
		}
	}
	else // Dodge mode
	{
		bool enemyBulletExists = false;
		int enemyBulletX;
		int enemyBulletY;
		EDirection enemyBulletDirection;

		if (bullet != nullptr)
		{
			enemyBulletExists = true;
			enemyBulletX = bullet->iX;
			enemyBulletY = bullet->iY;
			enemyBulletDirection = bullet->eDirection;
		}
		else
		{
			enemyBulletExists = false;
		}

		if (enemyBulletExists)
		{
			switch (enemyBulletDirection)
			{
				case EDirection::Down:
					if (GetPosY() > enemyBulletY && std::abs(GetPosX() - enemyBulletX < 4))
					{
						if (GetPosX() > enemyBulletX)
						{
							eDesiredLookDirection = EDirection::Right;
						}
						else
						{
							eDesiredLookDirection = EDirection::Left;
							
						}
						eDesiredAction = EAction::Move;
					}
					break;
				case EDirection::Up:
					if (GetPosY() < enemyBulletY && std::abs(GetPosX() - enemyBulletX < 4))
					{
						if (GetPosX() > enemyBulletX)
						{
							eDesiredLookDirection = EDirection::Right;
						}
						else
						{
							eDesiredLookDirection = EDirection::Left;

						}
						eDesiredAction = EAction::Move;
					}
					break;
				case EDirection::Left:
					if (GetPosX() < enemyBulletX && std::abs(GetPosY() - enemyBulletY < 2))
					{
						if (GetPosY() > enemyBulletY)
						{
							eDesiredLookDirection = EDirection::Down;
						}
						else
						{
							eDesiredLookDirection = EDirection::Up;

						}
						eDesiredAction = EAction::Move;
					}
					break;
				case EDirection::Right:
					if (GetPosX() > enemyBulletX && std::abs(GetPosY() - enemyBulletY) < 2)
					{
						if (GetPosY() > enemyBulletY)
						{
							eDesiredLookDirection = EDirection::Down;
						}
						else
						{
							eDesiredLookDirection = EDirection::Up;

						}
						eDesiredAction = EAction::Move;
					}
					break;
			}
		}
		else
		{
			/*if (pt)eDesiredLookDirection = EDirection::Down;
			eDesiredAction = EAction::Move;*/
		}
	}
}


