#include "Tank.h"

#include <windows.h>
#include "../Bullet.h"
#include "../TankInfo.h"
#include "../TanksManager.h"

CTank::CTank(std::string _sName, int _iX, int _iY, int _iColor)
{
	m_sName = _sName;
	m_iInitialX = _iX;
	m_iInitialY = _iY;
	m_iColor = _iColor;
}

std::string CTank::GetName() const
{
	return m_sName;
}

int CTank::GetColor() const
{
	return m_iColor;
}

int CTank::GetPosInitialX() const
{
	return m_iInitialX;
}

int CTank::GetPosInitialY() const
{
	return m_iInitialY;
}

int CTank::GetPosX() const
{
	return m_pTankInfo->iX;
}

int CTank::GetPosY() const
{
	return m_pTankInfo->iY;
}

void CTank::GetPos(int& iX_, int& iY_) const
{
	iX_ = m_pTankInfo->iX;
	iY_ = m_pTankInfo->iY;
}

void CTank::SetTankInfoRef(const CTankInfo* _pTankInfo)
{
	m_pTankInfo = _pTankInfo;
}

const CBullet* CTank::GetBullet() const
{
	return m_pTankInfo->pBullet;
}

void CTank::Draw() const
{
	int iHalfWidth = CTanksManager::s_iTankWidth / 2;
	int iHalfHeight = CTanksManager::s_iTankHeight / 2;

	int iX, iY;
	GetPos(iX, iY);

	CTanksManager::Render(iX - iHalfWidth, iY - iHalfHeight, IsExploding()
		? CTanksManager::s_sAsciiTankExploding[m_iExplodingFrame % 2]
		: eDesiredAction == EAction::Shoot
		? CTanksManager::s_sAsciiTankShooting[static_cast<int>(eDesiredLookDirection)]
		: CTanksManager::s_sAsciiTank[static_cast<int>(eDesiredLookDirection)],
		m_iColor);
}

bool CTank::ToBeRemoved() const
{
	if (m_iExplodingFrame > 10)
	{
		return true;
	}
	return false;
}

void CTank::UpdateExploding()
{
	int iHalfWidth = CTanksManager::s_iTankWidth / 2;
	int iHalfHeight = CTanksManager::s_iTankHeight / 2;

	m_iExplodingFrame++;
	int iX, iY;
	GetPos(iX, iY);
	CTanksManager::Render(iX - iHalfWidth, iY - iHalfHeight, m_iExplodingFrame > 9
		? CTanksManager::s_sAsciiTankExploding[2]
		: CTanksManager::s_sAsciiTankExploding[m_iExplodingFrame % 2], m_iColor, true);
}

bool CTank::IsExploding() const
{
	return m_iExplodingFrame > 0;
}

int CTank::GetHealth() const
{
	return m_pTankInfo->iHealth;
}

bool CTank::IsDead() const
{
	return m_pTankInfo->iHealth <= 0;
}
