//------------------------------------------------------------------------------
// Worm.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
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
  // class to design the various fields in the game
  //
  class Worm : public Field
  {
    private:
      int id;
      int hp;
      std::string name;
      std::vector<Weapon> weapons;

    public:
      Worm(int id, std::string name);

      virtual ~Worm();

      const std::string &getName() const;

      void setName(const std::string &name);

      int getId() const;

      int getHp() const;

      const std::vector<Weapon> &getWeapons() const;

      void damage(int points);

      char getCharacter() const override;
  };
}

#endif //SEP19_GROUP21486_WORM_H
