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
      int row_;
      int col_;

  public:
      Chest(FieldType type, int weapon_number, int row, int col);

      virtual ~Chest();

      int getIdChest();

      int getRow();

      int getCol();

      FieldType getType();
  };
}

#endif //SEP19_GROUP21486_CHEST_H
