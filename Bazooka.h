//
// Created by stefan on 24.04.19.
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
