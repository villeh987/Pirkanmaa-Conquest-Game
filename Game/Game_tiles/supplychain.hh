#ifndef SUPPLYCHAIN_HH
#define SUPPLYCHAIN_HH

#include "buildings/buildingbase.h"
#include "core/basicresources.h"
#include "core/coordinate.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {



class SupplyChain : public Course::BuildingBase
{
public:
    SupplyChain(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                const std::shared_ptr<Course::iObjectManager>& objectmanager,
                const std::shared_ptr<Course::PlayerBase> &owner,
                const int &tilespaces = 1,
                const Course::ResourceMap &buildcost = GameResourceMaps::SUPPLYCHAIN_BUILD_COST,
                const Course::ResourceMap& production = GameResourceMaps::SUPPLYCHAIN_PRODUCTION);

};


}


#endif // SUPPLYCHAIN_HH
