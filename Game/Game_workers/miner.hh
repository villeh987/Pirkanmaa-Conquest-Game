#ifndef MINER_HH
#define MINER_HH

#include "workers/workerbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {


/**
 * @brief The Miner class represents a miner worker in the game.
 *
 * Miner efficiency may e found in constants.hh!
 * Miner is extremely useful on Rock type tiles.
 *
 */
class Miner : public Course::WorkerBase
{
public:

    /**
     * @brief Disabled parameterless constructor.
     */
    Miner() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the GameEventHandler.
     * @param objectmanager points to the ObjectManager.
     * @param owner points to the owning player.
     * @param tilespaces (Optional) How many tilespaces does the building take.
     * @param cost (Optional) How many resources does it cost to assign worker.
     * @param efficiency (Optional) How good is the worker at his job.
     */
    Miner(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
          const std::shared_ptr<Course::iObjectManager> &objectmanager,
          const std::shared_ptr<Course::PlayerBase> &owner,
          const int &tilespaces = 1,
          const Course::ResourceMap &cost = GameResourceMaps::MINER_RECRUITMENT_COST,
          const Course::ResourceMapDouble &efficiency = GameResourceMaps::MINER_EFFICIENCY);


    /**
     * @brief Default destructor.
     */
    virtual ~Miner() = default;

    /**
     * @brief getType Returns a string describing objects type.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const;

    /**
     * @brief Performs the Worker's default action.
     */
    virtual void doSpecialAction() override;
};



} // Namespace Game




#endif // MINER_HH
