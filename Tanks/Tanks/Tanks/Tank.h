#pragma once

#include <string>

#include "../Direction.h"
#include "../Action.h"

class CBullet;
class CTankInfo;

class CTank
{
public:
	CTank(std::string _sName, int _iX, int _iY, int _iColor);

	virtual void Update() = 0;

	// To set the desired look direction (to shoot in that direction)
	EDirection eDesiredLookDirection = EDirection::Down;
	// Desired action
	EAction eDesiredAction = EAction::None;

	// Name
	std::string GetName() const;
	// Color
	int GetColor() const;
	// Initial Position
	int GetPosInitialX() const;
	int GetPosInitialY() const;
	// Position
	int GetPosX() const;
	int GetPosY() const;
	void GetPos(int& iX_, int& iY_) const;
	void SetTankInfoRef(const CTankInfo* _pTankInfo);
	// Bullet
	const CBullet* GetBullet() const;
	// Draw
	void Draw() const;
	// To be removed?
	bool ToBeRemoved() const;
	// Exploding
	void UpdateExploding();
	bool IsExploding() const;
	// Health
	int GetHealth() const;
	bool IsDead() const;

private:
	std::string m_sName = "Default";
	int m_iColor = 1;
	int m_iInitialX;
	int m_iInitialY;
	const CTankInfo* m_pTankInfo;
	int m_iExplodingFrame;
};
