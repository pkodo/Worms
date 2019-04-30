//------------------------------------------------------------------------------
// Field.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
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

      enum FieldType {AIR, EARTH, WATER, WORM, CHEST};

      //------------------------------------------------------------------------
      // Constructor
      //
      Field(FieldType type);

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
