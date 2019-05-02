//------------------------------------------------------------------------------
// Melee.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_MELEE_H
#define SEP19_GROUP21486_MELEE_H

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Melee Class
  // class to perform Weapon-operations
  //
  class Melee : public Weapon
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Melee();

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Melee Object. Is set to delete.
      // @param melee object to copy.
      //
      Melee(Melee& melee) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Melee object to another. Is set to delete.
      // @param melee Original with values to copy.
      //
      Melee& operator = (Melee& melee) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Melee() override;

  };
}


#endif //SEP19_GROUP21486_MELEE_H
