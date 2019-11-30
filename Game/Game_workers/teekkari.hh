#ifndef TEEKKARI_HH
#define TEEKKARI_HH

#include "workers/workerbase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {

/**
 * @brief The Teekkari class represents a Teekkari worker in the game.
 *
 * Teekkari efficiency may e found in constants.hh!
 * Teekkari is the most powerful worker in the Game, as it can destoy opponent
 * Player's buildings.
 * Teekkari can also have a Teekkarifight against opponents Teekkari.
 * Loser of the Teekkarifight loses his Teekkari - and also his honor.
 *
 */
class Teekkari : public Course::WorkerBase
{
public:

    /**
     * @brief Disabled parameterless constructor.
     */
    Teekkari() = delete;

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
    Teekkari(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             const int &tilespaces = 1,
             const Course::ResourceMap &cost = GameResourceMaps::TEEKKARI_RECRUITMENT_COST,
             const Course::ResourceMapDouble &efficiency = GameResourceMaps::TEEKKARI_EFFICIENCY);

    /**
     * @brief Default destructor.
     */
    virtual ~Teekkari() = default;

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




#endif // TEEKKARI_HH
