//------------------------------------------------------------------------------
// Command.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//
#include "Field.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Field::Field(FieldType type) : type_(type)
  {
  }

  //----------------------------------------------------------------------------
  char Field::getCharacter() const
  {
    char field_character = ' ';
    switch (type_)
    {
      case AIR:
        field_character = ' ';
        break;
      case EARTH:
        field_character = 'E';
        break;
      case WATER:
        field_character = 'W';
        break;
      case WORM:
        field_character = '~';
        break;
      case CHEST:
        field_character = '#';
        break;
    }
    return field_character;
  }

  //----------------------------------------------------------------------------
  Field::FieldType Field::getType() const
  {
    return type_;
  }

  //----------------------------------------------------------------------------
  void Field::setType(FieldType type)
  {
    type_ = type;
  }
}
