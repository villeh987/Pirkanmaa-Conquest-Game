#ifndef TEEKKARI_HH
#define TEEKKARI_HH

#include "workers/workerbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {


class Teekkari : public Course::WorkerBase
{
public:
    Teekkari(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             const int &tilespaces = 1,
             const Course::ResourceMap &cost = GameResourceMaps::TEEKKARI_RECRUITMENT_COST,
             const Course::ResourceMapDouble &efficiency = GameResourceMaps::TEEKKARI_EFFICIENCY);

    virtual std::string getType() const;

};

}




#endif // TEEKKARI_HH
