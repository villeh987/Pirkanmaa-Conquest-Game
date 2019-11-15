#ifndef SUPPLYCHAIN_HH
#define SUPPLYCHAIN_HH

#include "tiles/tilebase.h"
#include "core/basicresources.h"
#include "core/coordinate.h"
#include "core/resourcemaps.h"

namespace Game {



class SupplyChain : public Course::TileBase
{
public:
    SupplyChain(const Course::Coordinate& location,
                const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                const std::shared_ptr<Course::iObjectManager>& objectmanager,
                const unsigned int& max_build,
                const unsigned int& max_work,
                const Course::ResourceMap& production);

};


}


#endif // SUPPLYCHAIN_HH
