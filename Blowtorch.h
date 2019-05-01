//
// Created by stefan on 24.04.19.
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
