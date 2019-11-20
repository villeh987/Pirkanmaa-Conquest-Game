#ifndef SUPPLYCHAIN_HH
#define SUPPLYCHAIN_HH

#include "buildings/buildingbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {



class SupplyChain : public Course::BuildingBase
{
public:
    SupplyChain(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                const std::shared_ptr<Course::iObjectManager>& objectmanager,
                const std::shared_ptr<Course::PlayerBase>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& buildcost = GameResourceMaps::TUNITOWER_BUILD_COST,
                const Course::ResourceMap& production = GameResourceMaps::TUNITOWER_PRODUCTION);

    virtual std::string getType() const override;

};


}


#endif // SUPPLYCHAIN_HH
