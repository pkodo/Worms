//
// Created by stefan on 24.04.19.
//

#ifndef SEP19_GROUP21486_GUN_H
#define SEP19_GROUP21486_GUN_H

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Gun Class
  // class to perform Weapon-operations
  //
  class Gun : public Weapon
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Gun();

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Gun object to another. Is set to delete.
      // @param gun Original with values to copy.
      //
      Gun& operator = (Gun& gun) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Gun() override;

      //------------------------------------------------------------------------
      // Method
      // method to use the Weapon
      void action() const override;
  };
}

#endif //SEP19_GROUP21486_GUN_H
