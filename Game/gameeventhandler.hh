#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <memory>
#include <vector>

#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"


namespace Game {

class TileBase;
class PlayerBase;
class GameObject;
class Coordinate;

class GameEventHandler : public Course::iGameEventHandler
{


public:
    GameEventHandler();

    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource,
                        int amount);

    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                     Course::ResourceMap resources);
};



} // Namespace Game


#endif // GAMEEVENTHANDLER_HH
