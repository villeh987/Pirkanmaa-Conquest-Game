#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include <vector>
#include <string>
#include "core/basicresources.h"


namespace Game {

// Describes tiles that players cannot perform any actions on.
const std::vector<std::string> DULL_TILES = {"Water"};


const Course::ResourceMap STARTRESOURCES = {
    {Course::BasicResource::MONEY, 5000},
    {Course::BasicResource::FOOD, 5000},
    {Course::BasicResource::WOOD, 5000},
    {Course::BasicResource::STONE, 5000},
    {Course::BasicResource::ORE, 5000}
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

const std::string PENALTY_BUILD_TEXT =
        "Oh no, you tried to build on lava!";

const std::string PENALTY_ADDWORKER_TEXT =
        "Oh my, you tried to add worker on lava!";

const std::string NOT_ENOUGH_RESOURCES_TEXT = "Not enough resources!";








}
#endif // CONSTANTS_HH
