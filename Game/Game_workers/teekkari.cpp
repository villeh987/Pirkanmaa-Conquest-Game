#include "Game_workers/teekkari.hh"

namespace Game {


Teekkari::Teekkari(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                   const std::shared_ptr<Course::iObjectManager>& objectmanager,
                   const std::shared_ptr<Course::PlayerBase>& owner,
                   const int& tilespaces,
                   const Course::ResourceMap& cost,
                   const Course::ResourceMapDouble& efficiency):
    WorkerBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        cost,
        efficiency)

{
}




} // Namespace Game


