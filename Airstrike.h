//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_AIRSTRIKE_H
#define SEP19_GROUP21486_AIRSTRIKE_H

#include "Weapon.h"

namespace Sep
{
  class Airstrike : public Weapon
  {
    public:
    Airstrike(const std::string &name);

    virtual ~Airstrike();
  };
}


#endif //SEP19_GROUP21486_AIRSTRIKE_H