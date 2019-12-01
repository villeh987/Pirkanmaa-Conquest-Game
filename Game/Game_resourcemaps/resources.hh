#ifndef RESOURCES_HH
#define RESOURCES_HH


#include "core/basicresources.h"
#include "core/resourcemaps.h"

namespace Game {

namespace GameResourceMaps {


// Bulding - TuniTower
const Course::ResourceMap TUNITOWER_BUILD_COST {
    {Course::BasicResource::MONEY, 500},
    {Course::BasicResource::WOOD, 100},
    {Course::BasicResource::STONE, 500},
    {Course::BasicResource::ORE, 500}

};

const Course::ResourceMap TUNITOWER_PRODUCTION {
    {Course::BasicResource::MONEY, 6},
    {Course::BasicResource::FOOD, 9},
    {Course::BasicResource::WOOD, 6},
    {Course::BasicResource::STONE, 6},
    {Course::BasicResource::ORE, 9}
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


// Bulding - Mine
const Course::ResourceMap MINE_BUILD_COST {
    {Course::BasicResource::MONEY, 400},
    {Course::BasicResource::FOOD, 400},
    {Course::BasicResource::WOOD, 500}
};

const Course::ResourceMap MINE_PRODUCTION {
    {Course::BasicResource::MONEY, 110},
    {Course::BasicResource::STONE, 50},
    {Course::BasicResource::ORE, 100}
};


// Tile - Water

const Course::ResourceMap WATER_BP {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}
};

// Tile - Rock

const Course::ResourceMap ROCK_BP {
    {Course::BasicResource::MONEY, 2},
    {Course::BasicResource::FOOD, -1},
    {Course::BasicResource::WOOD, -1},
    {Course::BasicResource::STONE, 10},
    {Course::BasicResource::ORE, 10}
};

// Tile - Lava

const Course::ResourceMap LAVA_BP {
    {Course::BasicResource::MONEY, -10},
    {Course::BasicResource::FOOD, -10},
    {Course::BasicResource::WOOD, -10},
    {Course::BasicResource::STONE, -10},
    {Course::BasicResource::ORE, -10}
};



// Worker - Teekkari

const Course::ResourceMapDouble TEEKKARI_EFFICIENCY {
    {Course::BasicResource::MONEY, 2},
    {Course::BasicResource::FOOD, 1},
    {Course::BasicResource::WOOD, 1},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 1}
};

const Course::ResourceMap TEEKKARI_RECRUITMENT_COST = {
    {Course::BasicResource::MONEY, 500},
    {Course::BasicResource::FOOD, 500}
};


// Worker - Miner

const Course::ResourceMapDouble MINER_EFFICIENCY {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::FOOD, 1},
    {Course::BasicResource::WOOD, 1},
    {Course::BasicResource::STONE, 1.2},
    {Course::BasicResource::ORE, 1.5}
};

const Course::ResourceMap MINER_RECRUITMENT_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 50}
};

// Penalty (if build or add worker on lava)
const Course::ResourceMap PENALTY {
    {Course::BasicResource::MONEY, -100},
    {Course::BasicResource::FOOD, -100},
    {Course::BasicResource::WOOD, -100},
    {Course::BasicResource::STONE, -100},
    {Course::BasicResource::ORE, -100}
};

const Course::ResourceMap WORSHIP {
    {Course::BasicResource::MONEY, 250},
    {Course::BasicResource::FOOD, 250},
    {Course::BasicResource::WOOD, 250},
    {Course::BasicResource::STONE, 250},
    {Course::BasicResource::ORE, 250}
};




}

}


#endif // RESOURCES_HH
