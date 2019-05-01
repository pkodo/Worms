//
// Created by stefan on 24.04.19.
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
