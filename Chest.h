//
// Created by stefan on 19.04.19.
//

#ifndef SEP19_GROUP21486_CHEST_H
#define SEP19_GROUP21486_CHEST_H

#include "Field.h"

namespace Sep
{
  class Chest : public Field
  {
  private:
      FieldType chest_type_ = Field::CHEST;
      int weapon_number_;

  public:
      Chest(FieldType type, int weapon_number_);

      virtual ~Chest();

      int getIdChest();

      FieldType getType();
  };
}

#endif //SEP19_GROUP21486_CHEST_H
