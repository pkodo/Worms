//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_MELEE_H
#define SEP19_GROUP21486_MELEE_H

#include "Weapon.h"

namespace Sep
{
  class Melee : public Weapon
  {
    public:
    Melee(const std::string &name);

    virtual ~Melee();

  };
}


#endif //SEP19_GROUP21486_MELEE_H
