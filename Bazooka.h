//------------------------------------------------------------------------------
// Bazooka.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_BAZOOKA_H
#define SEP19_GROUP21486_BAZOOKA_H

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Bazooka Class
  // class to perform Weapon-operations
  //
  class Bazooka : public Weapon
  {

    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Bazooka();

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Bazooka Object. Is set to delete.
      // @param bazooka object to copy.
      //
      Bazooka(Bazooka& bazooka) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Bazooka object to another. Is set to delete.
      // @param bazooka Original with values to copy.
      //
      Bazooka& operator = (Bazooka& bazooka) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Bazooka() override;
  };
}


#endif //SEP19_GROUP21486_BAZOOKA_H
