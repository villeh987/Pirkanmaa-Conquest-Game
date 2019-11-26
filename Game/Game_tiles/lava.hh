#ifndef LAVA_HH
#define LAVA_HH

#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {

class Lava : public Course::TileBase
{
public:
    Lava(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 0,
         const unsigned int& max_work = 0,
         const Course::ResourceMap& production = GameResourceMaps::LAVA_BP);

    virtual std::string getType() const override;

};



} // Namespace Game




#endif // LAVA_HH
