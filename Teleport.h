//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_TELEPORT_H
#define SEP19_GROUP21486_TELEPORT_H


#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Teleport Class
  // class to perform Weapon-operations
  //
  class Teleport : public Weapon
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Teleport();

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Teleport object to another. Is set to delete.
      // @param teleport Original with values to copy.
      //
      Teleport& operator = (Teleport& teleport) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Teleport() override;

  };
}


#endif //SEP19_GROUP21486_TELEPORT_H
