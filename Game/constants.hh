#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include <vector>
#include <string>
#include "core/basicresources.h"


namespace Game {


/**
 * @brief Game constans are defined here.
 */


/**
 * @brief Describes tiles that players cannot perform any actions on.
 */
const std::vector<std::string> DULL_TILES = {"Water"};

/**
 * @brief Describes resources that Player's start with.
 */
const Course::ResourceMap STARTRESOURCES = {
    {Course::BasicResource::MONEY, 2000},
    {Course::BasicResource::FOOD, 2000},
    {Course::BasicResource::WOOD, 2000},
    {Course::BasicResource::STONE, 2000},
    {Course::BasicResource::ORE, 2000}
};

/**
 * @brief These factors are used when final points are calculated.
 */
const std::map<Course::BasicResource, double> GRADING_FACTORS= {
    {Course::BasicResource::MONEY, 1.5},
    {Course::BasicResource::FOOD, 1.1},
    {Course::BasicResource::WOOD, 1.3},
    {Course::BasicResource::STONE, 1.1},
    {Course::BasicResource::ORE, 1.3}
};

/**
 * @brief Maximum amoun of actions per round.
 */
const int MAX_ACTIONS = 2;

/**
 * @brief Maximum amount of rounds after which the Game ends.
 */
const int MAX_ROUDS = 100;

/**
 * @brief How many Teekkaris a Player may have at a time.
 */
const int MAX_TEEKKARIS_PER_PLAYER = 1;

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

const std::string MAX_TEEKKARIS_TEXT = "Only" + std::to_string(MAX_TEEKKARIS_PER_PLAYER) + "Teekkari(s) allowed per player!";

const std::string GAME_OVER_TEXT = "GAME OVER!";

const std::string WORSHIP_TEXT = "You feel like your potential is unlimited!";


} // Namespace Game

#endif // CONSTANTS_HH
