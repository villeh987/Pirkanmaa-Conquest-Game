#ifndef MINE_HH
#define MINE_HH

#include "buildings/buildingbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {


class Mine : public Course::BuildingBase
{
public:
    Mine(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
         const std::shared_ptr<Course::iObjectManager> &objectmanager,
         const std::shared_ptr<Course::PlayerBase> &owner,
         const int &tilespaces = 1,
         const Course::ResourceMap &buildcost = GameResourceMaps::MINE_BUILD_COST,
         const Course::ResourceMap &production = GameResourceMaps::MINE_PRODUCTION);

    virtual std::string getType() const override;
};



} // Namespace Game


#endif // MINE_HH
