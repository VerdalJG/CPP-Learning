#include "PlayerTank.h"

#include <windows.h>

CPlayerTank::CPlayerTank(int _iX, int _iY, int _iColor)
  : CTank("Fer", _iX, _iY, _iColor)
{
}

void CPlayerTank::Update()
{
	eDesiredAction = EAction::None;

  short uLeftKeyState = GetKeyState(VK_LEFT);
	short uRightKeyState = GetKeyState(VK_RIGHT);
	short uUpKeyState = GetKeyState(VK_UP);
	short uDownKeyState = GetKeyState(VK_DOWN);
	short uShootKeyState = GetKeyState(0x53);

	if ((uLeftKeyState & 0x8000) != 0)
	{
		eDesiredAction = EAction::Move;
		eDesiredLookDirection = EDirection::Left;
	}
	else if ((uRightKeyState & 0x8000) != 0)
	{
		eDesiredAction = EAction::Move;
		eDesiredLookDirection = EDirection::Right;
	}
	else if ((uUpKeyState & 0x8000) != 0)
	{
		eDesiredAction = EAction::Move;
		eDesiredLookDirection = EDirection::Up;
	}
	else if ((uDownKeyState & 0x8000) != 0)
	{
		eDesiredAction = EAction::Move;
		eDesiredLookDirection = EDirection::Down;
	}

	if ((uShootKeyState & 0x8000) != 0)
	{
		eDesiredAction = EAction::Shoot;
	}
}