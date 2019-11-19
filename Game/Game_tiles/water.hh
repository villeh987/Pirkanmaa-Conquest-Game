#ifndef WATER_HH
#define WATER_HH
#include "tiles/tilebase.h"

namespace Game {


class Water : public Course::TileBase
{
public:

    Water() = delete;

    Water(const Course::Coordinate& location,
          const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const unsigned int& max_build = 0,
          const unsigned int& max_work = 0,
          //huom, tänne tarvii tehdä muutoksia. Eli tarvitaan oma resources-luokka.
          const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP
          );

    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in forest adds
     * one hold-marker to the building.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building) override;


};

}



#endif // WATER_HH
