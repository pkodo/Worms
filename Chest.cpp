//
// Created by stefan on 19.04.19.
//

#include "Chest.h"

namespace Sep
{
    Chest::Chest(int weapon_number, int row, int col)
      : Field(CHEST), weapon_number_(weapon_number),
        row_(row), col_(col)
    {
    }

    Chest::~Chest()
    = default;

    Chest::FieldType Chest::getType()
    {
        return chest_type_;
    }

    int Chest::getIdChest()
    {
        return weapon_number_;
    }

    void Chest::setPosition(int row, int col)
    {
        row_ = row;
        col_ = col;
    }

    int Chest::getRow()
    {
        return row_;
    }

    int Chest::getCol()
    {
        return col_;
    }
}
