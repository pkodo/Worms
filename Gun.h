//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_GUN_H
#define SEP19_GROUP21486_GUN_H

#include "Weapon.h"

namespace Sep
{
  class Gun : public Weapon
  {
    public:
    Gun(const std::string &name);

    virtual ~Gun();
  };
}

#endif //SEP19_GROUP21486_GUN_H
