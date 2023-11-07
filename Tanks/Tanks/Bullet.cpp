#include "Bullet.h"

#include "Tanks/Tank.h"
#include "TanksManager.h"
#include "Map.h"

bool CBullet::CollisionCheck(const CTank*& pCollidingTank_)
{
	pCollidingTank_ = nullptr;
	// Check bullet againt tanks
	for(const CTank* pTank : CTanksManager::GetInstance().GetTanks())
	{
		if (abs(iX - pTank->GetPosX()) < 3 && abs(iY - pTank->GetPosY()) < 2)
		{
			pCollidingTank_ = pTank;
			return true;
		}
	}
	// Check bullet against map
	if (CTanksManager::GetInstance().GetMap().CheckBulletCollision(this))
	{
		return true;
	}
	return false;
}
