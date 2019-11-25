#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include <vector>
#include <string>
#include "core/basicresources.h"


namespace Game {

// Describes tiles that players cannot perform any actions on.
const std::vector<std::string> DULL_TILES = {"Water"};


const Course::ResourceMap STARTRESOURCES = {
    {Course::BasicResource::MONEY, 10000},
    {Course::BasicResource::FOOD, 11000},
    {Course::BasicResource::WOOD, 12000},
    {Course::BasicResource::STONE, 13000},
    {Course::BasicResource::ORE, 14000}
};

}
#endif // CONSTANTS_HH
