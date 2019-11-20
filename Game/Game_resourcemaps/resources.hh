#ifndef RESOURCES_HH
#define RESOURCES_HH


#include "core/basicresources.h"
#include "core/resourcemaps.h"

namespace Game {

namespace GameResourceMaps {


// Bulding - TuniTower
const Course::ResourceMap TUNITOWER_BUILD_COST {
    {Course::BasicResource::MONEY, 101},
    {Course::BasicResource::FOOD, 102},
    {Course::BasicResource::WOOD, 103}
};

const Course::ResourceMap TUNITOWER_PRODUCTION {
    {Course::BasicResource::MONEY, 6},
    {Course::BasicResource::FOOD, 9}
};


// Bulding - Supplychain
const Course::ResourceMap SUPPLYCHAIN_BUILD_COST {
    {Course::BasicResource::MONEY, 69},
    {Course::BasicResource::FOOD, 69},
    {Course::BasicResource::WOOD, 69}
};

const Course::ResourceMap SUPPLYCHAIN_PRODUCTION {
    {Course::BasicResource::MONEY, 123},
    {Course::BasicResource::FOOD, 321}
};


// Tile - Water

const Course::ResourceMap WATER_BP {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}
};



}
}


#endif // RESOURCES_HH
