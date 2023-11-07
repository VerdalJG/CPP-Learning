#pragma once

#include "Tank.h"

class VFCTank : public CTank
{
public:
	VFCTank(int _iX, int _iY, int _iColor);

	virtual void Update() override;
};
