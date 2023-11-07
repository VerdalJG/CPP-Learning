#pragma once

#include <vector>
#include <list>
#include "ISingleton.h"
#include "Tanks/Tank.h"
#include "Map.h"

class CTanksManager : public ISingleton<CTanksManager>
{
public:
	static const int s_iInitialTankHealth = 4;
	static const int s_iBulletSpeed = 2;
	static const int s_iTankHeight = 3;
	static const int s_iTankWidth = 5;

	static const char* s_sAsciiTank[];
	static const size_t s_uAsciiTankSize;
	static const char* s_sAsciiTankShooting[];
	static const size_t s_uAsciiTankShootingSize;
	static const char* s_sAsciiTankExploding[];
	static const size_t s_uAsciiTankExplodingSize;
	static const char* s_sAsciiBullet[];
	static const size_t s_uAsciiBulletSize;

	~CTanksManager();

	// To get all tanks (alive or not)
	const std::vector<const CTank*>& GetAllTanks() { return m_tAllTanks; }
	// To get all alive tanks
	const std::list<const CTank*>& GetTanks() { return m_tTanks; }
	// To get the map
	const CMap& GetMap() { return m_oMap; }

	// Add tank to the manager
	void AddTank(CTank* _pTank);
	// Update the manager
	void Update();

	// Utility to render string
	static void Render(short _iX, short _iY, const char* _sString, int _iColor = 15, bool _bDrawBlankSpaces = false);

private:
	void SetTankInfo(CTank* _pTank, int _iX, int _iY);
	void TryMoveTank(CTank* _pTank);

	bool TryFireBullet(CTankInfo* _pTankInfo);
	void ProcessTankImpact(const CTank* _pTank);
	void UpdateBullet(CTankInfo* _pTankInfo, bool _bAllowMovement);
	void RemoveDeadTanks();

	bool IsGameFinished() const;

private:
	std::vector<const CTank*> m_tAllTanks;
	std::list<const CTank*> m_tTanks;
	CMap m_oMap;

	std::vector<CTankInfo*> m_tTankInfos;
};
