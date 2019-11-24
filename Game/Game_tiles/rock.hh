#ifndef ROCK_HH
#define ROCK_HH
#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"


namespace Game {

class Rock : public Course::TileBase
{
public:
    Rock() = delete;

    Rock(const Course::Coordinate& location,
          const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const unsigned int& max_build = 1,
          const unsigned int& max_work = 5,
          const Course::ResourceMap& production = GameResourceMaps::WATER_BP
          );

    virtual ~Rock() = default;
    virtual std::string getType() const;

};



}



#endif // ROCK_HH
