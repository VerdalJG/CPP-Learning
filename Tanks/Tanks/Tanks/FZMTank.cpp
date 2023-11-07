#include "FZMTank.h"

CFZMTank::CFZMTank(int _iX, int _iY, int _iColor)
  : CTank("Fer", _iX, _iY, _iColor)
{
}

void CFZMTank::Update()
{
	eDesiredAction = EAction::None;

	int iRandomIndex = rand() % 6;
	if (iRandomIndex < static_cast<int>(EDirection::Count))
	{
		eDesiredLookDirection = static_cast<EDirection>(iRandomIndex);
		eDesiredAction = EAction::Move;
	}

	if (GetBullet() == nullptr)
	{
		eDesiredAction = EAction::Shoot;
	}
}


