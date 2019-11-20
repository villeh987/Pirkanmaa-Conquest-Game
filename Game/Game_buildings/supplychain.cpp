#include "Game_buildings/supplychain.hh"



namespace Game {



SupplyChain::SupplyChain(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                         const std::shared_ptr<Course::iObjectManager> &objectmanager,
                         const std::shared_ptr<Course::PlayerBase> &owner,
                         const int &tilespaces,
                         const Course::ResourceMap &buildcost,
                         const Course::ResourceMap &production)
    :BuildingBase(
         eventhandler,
         objectmanager,
         owner,
         tilespaces,
         buildcost,
         production
         )
{
}

std::string SupplyChain::getType() const
{
    return "SupplyChain";
}




}

