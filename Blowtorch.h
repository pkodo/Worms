//------------------------------------------------------------------------------
// Blowtorch.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_BLOWTORCH_H
#define SEP19_GROUP21486_BLOWTORCH_H

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Blowtorch Class
  // class to perform Weapon-operations
  //
  class Blowtorch : public Weapon
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Blowtorch();

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Blowtorch Object. Is set to delete.
      // @param blowtorch object to copy.
      //
      Blowtorch(Blowtorch& blowtorch) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Bazooka object to another. Is set to delete.
      // @param bazooka Original with values to copy.
      //
      Blowtorch& operator = (Blowtorch& blowtorch) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Blowtorch() override;
  };
}


#endif //SEP19_GROUP21486_BLOWTORCH_H
