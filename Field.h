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
#ifndef SEP_FIELD_H
#define SEP_FIELD_H

namespace Sep
{
  //----------------------------------------------------------------------------
  // Field Class
  // class to design the various fields in the game
  //
  class Field
  {
    public:
      //------------------------------------------------------------------------
      // Enum describing the current field type
      //
      enum FieldType {AIR, EARTH, WATER, WORM, CHEST};

      //------------------------------------------------------------------------
      // Constructor
      //
      explicit Field(FieldType type);

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Field object to another. Is set to delete.
      // @param field Original with values to copy.
      //
      Field& operator = (Field& field) = delete;

      //------------------------------------------------------------------------
      // Getter Methods
      // @return Returns the character of a field.
      //
      virtual char getCharacter() const;

      //------------------------------------------------------------------------
      // Getter Methods
      // @return Returns the type of a field.
      //
      FieldType getType() const;

      //------------------------------------------------------------------------
      // Setter Methods
      // @param type set the attribute to type.
      //
      void setType(FieldType type);

    private:
      //------------------------------------------------------------------------
      // Variable for saving the current type of a field.
      //
      FieldType type_;
  };
}

#endif //SEP_FIELD_H
