#ifndef WATER_HH
#define WATER_HH
#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"

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
          const Course::ResourceMap& production = GameResourceMaps::WATER_BP
          );

    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;


};

}



#endif // WATER_HH
