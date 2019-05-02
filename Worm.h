//------------------------------------------------------------------------------
// Worm.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_WORM_H
#define SEP19_GROUP21486_WORM_H

#include "Field.h"
#include "Weapon.h"

#include <string>
#include <vector>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Worm Class
  // class to execute Worm operations
  //
  class Worm : public Field
  {

    public:
      //------------------------------------------------------------------------
      //Constructor
      //
      Worm(int id, std::string name);

      //------------------------------------------------------------------------
      //Destructor
      //
      virtual ~Worm();

      //------------------------------------------------------------------------
      //Getter Method
      //get the name of the worm
      //
      const std::string& getName() const;

      //------------------------------------------------------------------------
      //Setter Method
      //set the name of the worm
      //
      void setName(const std::string& name);

      //------------------------------------------------------------------------
      //Getter Method
      //get the identificationnumber of the worm
      //
      int getId() const;

      //------------------------------------------------------------------------
      //Getter Method
      //get the healthpoints of the worm
      //
      int getHp() const;

      //------------------------------------------------------------------------
      //Getter Method
      //get the identificationnumber of the worm
      //
      int getRow() const;

      //------------------------------------------------------------------------
      //Getter Method
      //get the number of the column from the worm
      //
      int getCol() const;

      //------------------------------------------------------------------------
      //Getter Method
      //get Weapons of the vector
      //
      std::vector<Weapon>& getWeapons();

      //------------------------------------------------------------------------
      //damage Method
      //calculate the damage
      //
      void damage(int points);

      //------------------------------------------------------------------------
      //Setter Method
      //sets the row and column
      //
      void setPosition(int row, int col);

      //------------------------------------------------------------------------
      //Setter Method
      //sets the healthpoints
      //
      void setHp(int hp);

      //------------------------------------------------------------------------
      //Getter Method
      //gets the character which identifice the player getting the worm
      //
      char getCharacter() const override;

      //------------------------------------------------------------------------
      //Setter Method
      //sets the weapons
      //
      void setWeapons();

      //------------------------------------------------------------------------
      //Getter Method
      //get the current weapon of the worm
      //
      int getCurrentWeapon() const;

      //------------------------------------------------------------------------
      //Setter Method
      //sets the current weapon of the worm
      //
      void setCurrentWeapon(int current_weapon);

    private:
      //the identificationnumber
      int id_;
      //healthnumber
      int hp_;
      //number of the row within the board
      int row_;
      //number of the column within the board
      int col_;
      //name of the worm
      std::string name_;
      //Weapons, which are stored seperatly in a vector
      std::vector<Weapon> weapons_;
      //number of the current weapon
      int current_weapon_;

  };
}

#endif //SEP19_GROUP21486_WORM_H
