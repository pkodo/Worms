//
// Created by stefan on 17.04.19.
//

#ifndef SEP19_GROUP21486_WEAPON_H
#define SEP19_GROUP21486_WEAPON_H

#include <string>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Weapon Class
  // class to design the various weapons in the game
  //
  class Weapon
  {
    public:
      //Constructor
      Weapon();
      //Constructor
      Weapon(const std::string &name, int ammo, int damage);
      //Destructor
      virtual ~Weapon();
      //Getter Method
      //get ammunition
      int getAmmo() const;

      //decreaseAmmo Method
      //decrease the ammunition
      void decreaseAmmo();

      //increaseAmmo Method
      //increase the ammunition
      void increaseAmmo();

      //Getter Method
      //gets the name of the weapen
      const std::string &getName() const;

      //getDamage Method
      //Calculates the Damage
      int getDamage() const;
      virtual void action() const;

    private:
      //Variable for the name of the weapon
      std::string name_;
      //Variable for the ammunition of the weapon
      int ammo_;
      //Variable for the damage of the weapon
      int damage_;
  };
}

#endif //SEP19_GROUP21486_WEAPON_H
