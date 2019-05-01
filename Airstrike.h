//
// Created by stefan on 24.04.19.
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
