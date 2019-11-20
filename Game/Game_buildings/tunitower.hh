#ifndef TUNITOWER_HH
#define TUNITOWER_HH

#include <memory>

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "core/basicresources.h"

namespace Game {



class TuniTower : public Course::BuildingBase
{
public:
    TuniTower(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::FARM_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::FARM_PRODUCTION);

    virtual std::string getType() const override;
};




}


#endif // TUNITOWER_HH
