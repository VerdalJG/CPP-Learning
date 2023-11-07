#pragma once

#include "Direction.h"

class CTank;

class CBullet
{
public:
	short iX;
	short iY;
	EDirection eDirection;

	bool CollisionCheck(const CTank*& pCollidingTank_);
};

