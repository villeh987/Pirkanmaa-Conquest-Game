#ifndef TUNITOWER_HH
#define TUNITOWER_HH

#include <memory>

#include "buildings/buildingbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {


/**
 * @brief The TuniTower class represents a TuniTower-building in the game.
 *
 */
class TuniTower : public Course::BuildingBase
{
public:

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the GameEventHandler.
     * @param objectmanager points to the ObjectManager.
     * @param owner points to the owning player.
     * @param tilespaces (Optional) How many tilespaces does the building take.
     * @param buildcost (Optional) How much resources does it cost to build building.
     * @param production (Optional) What resources does the building give.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    TuniTower(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameResourceMaps::TUNITOWER_BUILD_COST,
            const Course::ResourceMap& production = GameResourceMaps::TUNITOWER_PRODUCTION);

    /**
     * @brief getType Returns a string describing objects type.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const override;
};




}


#endif // TUNITOWER_HH
