//
// Created by stefan on 19.04.19.
//

#include "Chest.h"

namespace Sep
{
    Chest::Chest(FieldType type, int weapon_number_) : Field(CHEST), weapon_number_(weapon_number_)
    {
    }

    Chest::~Chest()
    {

    }

    Chest::FieldType Chest::getType()
    {
        return chest_type_;
    }

    int Chest::getIdChest()
    {
        return weapon_number_;
    }
}