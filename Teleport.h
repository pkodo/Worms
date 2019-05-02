//------------------------------------------------------------------------------
// Teleport.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
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
      // Copy Constructor
      // Makes a copy of another Teleport Object. Is set to delete.
      // @param teleport object to copy.
      //
      Teleport(Teleport& teleport) = delete;

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
