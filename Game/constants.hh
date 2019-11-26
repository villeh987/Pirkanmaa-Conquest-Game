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

const int MAX_ACTIONS = 2;

const std::string ROUND_START_NOCLICK_TEXT = "Select a tile:";

const std::string ROUND_START_CLICKED_TEXT = "Choose action:";

const std::string ROUND_MAX_ACTIONS_TEXT = "Max actions reached. End turn.";

const std::string ROUND_WRONG_OWNER_TEXT =
        "You came into the wrong house, fool!";

const std::string ROUND_DULL_TILE_CLICKED_TEXT =
        "You cannot perform any actions on this tile.";

const std::string ROUND_LAVA_CLICKED_TEXT = "Watch out, things are getting HOT!";








}
#endif // CONSTANTS_HH
