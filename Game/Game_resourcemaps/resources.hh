#ifndef RESOURCES_HH
#define RESOURCES_HH


#include "core/basicresources.h"
#include "core/resourcemaps.h"

namespace Game {


const Course::ResourceMap TUNITOWER_BUILD_COST {
    {Course::BasicResource::MONEY, 101},
    {Course::BasicResource::FOOD, 102},
    {Course::BasicResource::WOOD, 103}
};

}


#endif // RESOURCES_HH
