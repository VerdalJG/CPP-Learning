// practica4.cpp
//
#include <stdio.h>
#include "consola.h"
#include <iostream>

struct TEntity;
typedef void (*funcEntity)(TEntity*);


// ***************************************************************************************
// ENTIDAD
// ***************************************************************************************
struct TEntity
{
	int m_ix;
	int m_iy;
	funcEntity* m_funcs;
	TEntity(funcEntity* funcs, int x, int y)
	{
		m_ix = x;
		m_iy = y;
		m_funcs = funcs;
	}
};

void PaintA(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("A");
}

void PaintB(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("B");
}

void PaintC(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("C");
}

void PaintD(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("D");
}

void CheckBoundaries(TEntity* _pEntity)
{
	constexpr int s_iMaxX = 20;
	constexpr int s_iMaxY = 10;

	if (_pEntity->m_ix > s_iMaxX)
	{
		_pEntity->m_ix = 0;
	}
	else if (_pEntity->m_ix < 0)
	{
		_pEntity->m_ix = s_iMaxX;
	}
	if (_pEntity->m_iy > s_iMaxY)
	{
		_pEntity->m_iy = 0;
	}
	else if (_pEntity->m_iy < 0)
	{
		_pEntity->m_iy = s_iMaxY;
	}
}

void MoveLeft(TEntity* _pEntity)
{
	_pEntity->m_ix--;
	CheckBoundaries(_pEntity);
}

void MoveRight(TEntity* _pEntity)
{
	_pEntity->m_ix++;
	CheckBoundaries(_pEntity);
}

void MoveDown(TEntity* _pEntity)
{
	_pEntity->m_iy++;
	CheckBoundaries(_pEntity);
}

void MoveUp(TEntity* _pEntity)
{
	_pEntity->m_iy--;
	CheckBoundaries(_pEntity);
}

void MoveRandom(TEntity* _pEntity)
{
	int iRand = rand() % 2;
	int iRand2 = rand() % 2;
	_pEntity->m_ix += iRand == 0 ? 1 : -1;
	_pEntity->m_iy += iRand2 == 0 ? 1 : -1;
	CheckBoundaries(_pEntity);
}

// ***************************************************************************************
// MAIN
// ***************************************************************************************
int main()
{
	clear();

	Sleep(2000);

	funcEntity functionContainer1[2]
	{
		&PaintA,
		&MoveRandom
	};

	funcEntity functionContainer2[2]
	{
		&PaintB,
		&MoveRandom
	};

	funcEntity functionContainer3[2]
	{
		&PaintC,
		&MoveRandom
	};

	funcEntity functionContainer4[2]
	{
		&PaintD,
		&MoveRandom
	};

	TEntity* tEntities[4];
	tEntities[0] = new TEntity(functionContainer1, 2, 2);
	tEntities[1] = new TEntity(functionContainer2, 2, 6);
	tEntities[2] = new TEntity(functionContainer3, 2, 10);
	tEntities[3] = new TEntity(functionContainer4, 2, 14);

	while (true)
	{
		for (unsigned int uIndex = 0; uIndex < 4; uIndex++)
		{
			if (tEntities[uIndex])
			{
				(*(tEntities[uIndex]->m_funcs))(tEntities[uIndex]);
				(*(tEntities[uIndex]->m_funcs + 1))(tEntities[uIndex]);
			}
		}

		for (unsigned int uIndex = 0; uIndex < 4; uIndex++)
		{
			for (unsigned int uIndex2 = uIndex + 1; uIndex2 < 4; uIndex2++)
			{
				if (tEntities[uIndex] &&
					tEntities[uIndex2] &&
					tEntities[uIndex]->m_ix == tEntities[uIndex2]->m_ix &&
					tEntities[uIndex]->m_iy == tEntities[uIndex2]->m_iy)
				{
					gotoxy(tEntities[uIndex]->m_ix, tEntities[uIndex]->m_iy);
					printf("X");

					delete tEntities[uIndex];
					tEntities[uIndex] = nullptr;
					delete tEntities[uIndex2];
					tEntities[uIndex2] = nullptr;
				}
			}
		}

		Sleep(100);
		clear();
	}
	// Example
	int (*funcPointer)(int, int) = &add;
	funcPointer(2, 3);
}
// Example
int add(int a, int b)
{
	return (a + b);
}

