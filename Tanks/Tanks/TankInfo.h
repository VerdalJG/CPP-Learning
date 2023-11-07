#pragma once

class CTank;
class CBullet;

class CTankInfo
{
public:
	CTank* pTank = nullptr;
	int iX = 0;
	int iY = 0;
	int iHealth = 0;
	CBullet* pBullet = nullptr;
	bool bExploding = false;
};
