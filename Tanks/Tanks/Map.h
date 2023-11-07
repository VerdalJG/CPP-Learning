#pragma once

#include <string>

class CTank;
class CBullet;

class CMap
{
public:
	CMap();

	const std::string& GetAscii() const;
	virtual int GetHeight() const;
	virtual int GetWidth() const;

	bool IsWall(int _iX, int _iY) const;
	bool MoveCheck(CTank* _pMovingTank, int _iX, int _iY) const;
	bool CheckBulletCollision(CBullet* _pBullet) const;

protected:
	std::string m_sAscii;
};
