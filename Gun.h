//------------------------------------------------------------------------------
// Gun.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
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
      // Copy Constructor
      // Makes a copy of another Gun Object. Is set to delete.
      // @param gun object to copy.
      //
      Gun(Gun& gun) = delete;

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

  };
}

#endif //SEP19_GROUP21486_GUN_H
