#ifndef MINER_HH
#define MINER_HH

#include "workers/workerbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {

class Miner : public Course::WorkerBase
{
public:
    Miner(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
          const std::shared_ptr<Course::iObjectManager> &objectmanager,
          const std::shared_ptr<Course::PlayerBase> &owner,
          const int &tilespaces = 1,
          const Course::ResourceMap &cost = GameResourceMaps::MINER_RECRUITMENT_COST,
          const Course::ResourceMapDouble &efficiency = GameResourceMaps::MINER_EFFICIENCY);

    virtual std::string getType() const;

    virtual void doSpecialAction() override;
};



} // Namespace Game




#endif // MINER_HH
