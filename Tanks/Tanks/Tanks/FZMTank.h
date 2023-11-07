#pragma once

#include "Tank.h"

class CFZMTank : public CTank
{
public:
  CFZMTank(int _iX, int _iY, int _iColor);

  virtual void Update() override;
};
