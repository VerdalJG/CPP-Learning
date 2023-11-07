#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>

#include "TanksManager.h"
#include "Tanks/PlayerTank.h"
#include "Tanks/FZMTank.h"
#include "Tanks/VFCTank.h"

#pragma execution_character_set( "utf-8" )

static void CreateTanks()
{
	const CMap& rMap = CTanksManager::GetInstance().GetMap();

	// Añadir aqui los tanques
	CTanksManager::GetInstance().AddTank(new CPlayerTank(10, 6, 13));
	CTanksManager::GetInstance().AddTank(new VFCTank(rMap.GetWidth() - 10, rMap.GetHeight() - 7, 14));
}


int main()
{
	CTanksManager::CreateSingleton();

	CreateTanks();

	SetConsoleOutputCP(65001);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	HWND wConsole = GetConsoleWindow();
	RECT r;
	GetWindowRect(wConsole, &r); //stores the console's current dimensions
	MoveWindow(wConsole, r.left, r.top, 1200, 1200, TRUE);

	system("cls");

	while (CTanksManager::GetInstance().GetTanks().size() > 1)
	{
		CTanksManager::GetInstance().Update();

		Sleep(10);
	}

	CTanksManager::DestroySingleton();
}