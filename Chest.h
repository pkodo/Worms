//------------------------------------------------------------------------------
// Chest.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
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

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Chest(int weapon_number, int row, int col);

    //------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Chest Object. Is set to delete.
    // @param chest object to copy.
    //
    Chest(Chest& chest) = delete;

    //--------------------------------------------------------------------------
    // Assignment Operator
    // Used to assign one Chest object to another. Is set to delete.
    // @param chest Original with values to copy.
    //
    Chest& operator = (Chest& chest) = delete;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Chest();

    //--------------------------------------------------------------------------
    // Getter Method
    // returns the weapon_number
    //
    int getIdChest();

    //--------------------------------------------------------------------------
    // Setter Method
    // sets the coordinates
    // @param row is the new row position of the object
    // @param col is the new col position of the object
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

  private:

    //--------------------------------------------------------------------------
    // The first Variable declares the Type of chest_type_
    // The other Variables define the number of the weapon, and the coordinates
    //
    FieldType chest_type_ = Field::CHEST;
    int weapon_number_;
    int row_;
    int col_;
  };
}

#endif //SEP19_GROUP21486_CHEST_H
