#include "water.hh"

//#include "tiles/tilebase.h"


namespace Game {




Water::Water(const Course::Coordinate& location,
      const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
      const std::shared_ptr<Course::iObjectManager>& objectmanager,
      const unsigned int& max_build,
      const unsigned int& max_work,
      const Course::ResourceMap& production
      ):
    Course::TileBase(location,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{
}

std::string Water::getType() const
{
    return "Water";
}

} // namespace Game

