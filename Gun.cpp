//
// Created by stefan on 24.04.19.
//

#include "Gun.h"

namespace Sep
{

  Gun::Gun() : Weapon("gun", 1, 25) // inf
  {
  }

  Gun::~Gun()
  = default;

  void Gun::action() const
  {
    Weapon::action();
  }
}
