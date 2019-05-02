//------------------------------------------------------------------------------
// Airstrike.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_AIRSTRIKE_H
#define SEP19_GROUP21486_AIRSTRIKE_H

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Airstrike Class
  // class to perform Weapon-operations
  //
  class Airstrike : public Weapon
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Airstrike();

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Airstrike Object. Is set to delete.
      // @param airstrike object to copy.
      //
      Airstrike(Airstrike& airstrike) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Airstrike object to another. Is set to delete.
      // @param airstrike Original with values to copy.
      //
      Airstrike& operator = (Airstrike& airstrike) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Airstrike() override;
  };
}


#endif //SEP19_GROUP21486_AIRSTRIKE_H
