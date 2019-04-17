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
      Weapon(std::string name);

      virtual ~Weapon();

      int getAmmo() const;

      void setAmmo(int ammo);

      const std::string &getName() const;

      int getDamage() const;

    private:
      std::string name;
      int ammo;
      int damage;
  };
}

#endif //SEP19_GROUP21486_WEAPON_H
