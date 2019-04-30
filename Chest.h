//
// Created by stefan on 19.04.19.
//

#ifndef SEP19_GROUP21486_CHEST_H
#define SEP19_GROUP21486_CHEST_H

#include "Field.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Chest Class
  // class to create and design the chest
  //
  class Chest : public Field
  {
  private:
    //--------------------------------------------------------------------------
    // The first Variable declares the Type of chest_type_
    // The other Variables define the number of the weapon, and the coordinates
    //
    FieldType chest_type_ = Field::CHEST;
    int weapon_number_;
    int row_;
    int col_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Chest(int weapon_number, int row, int col);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Chest();

    //------------------------------------------------------------------------
    // Getter Method
    // returns the weapon_number
    //
    int getIdChest();

    //--------------------------------------------------------------------------
    // Setter Method
    // sets the coordinates
    //
    void setPosition(int row, int col);

    //--------------------------------------------------------------------------
    // Getter Method
    // returns the row number
    //
    int getRow();

    //--------------------------------------------------------------------------
    // Getter Method
    // returns the col number
    //
    int getCol();
    //------------------------------------------------------------------------
    // Getter Method
    // returns the chest_type_
    //
    FieldType getType();
  };
}

#endif //SEP19_GROUP21486_CHEST_H
