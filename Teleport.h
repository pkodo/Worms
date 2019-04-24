//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_TELEPORT_H
#define SEP19_GROUP21486_TELEPORT_H


#include "Weapon.h"

namespace Sep
{
  class Teleport : public Weapon
  {
    public:
    Teleport(const std::string &name);

    virtual ~Teleport();

  };
}


#endif //SEP19_GROUP21486_TELEPORT_H
