#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <memory>
#include <vector>
#include <utility>
#include <QColor>

#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "player.hh"
#include "Game_errors/resourceerror.hh"
#include "constants.hh"
#include "objectmanager.hh"



namespace Game {

class TileBase;
class PlayerBase;
class GameObject;
class Coordinate;

class GameEventHandler : public Course::iGameEventHandler
{


public:
    GameEventHandler();

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource,
                        int amount);
    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                     Course::ResourceMap resources);

    /**
     * @brief Calls addPlayers, addColors and startGame.
     * @param names Player names to be added.
     * @param colors Player colors to be added.
     */
    void initNewGame(QList<QString> names, QList<QColor> colors);

    /**
     * @brief Changes player_in_turn_ and increments rounds_.
     */
    void changeTurn();

    /**
     * @brief Calls generateResources for all tiles owned by player_in_turn_.
     */
    void handleGenerateResources(std::vector<std::shared_ptr<Course::TileBase> > tiles);

    /**
     * @brief Returns pointer to current Player in turn.
     * @return shared_ptr to current Player in turn.
     */
    std::shared_ptr<Game::Player> getPlayerInTurn();

    /**
     * @brief Returns all Players as pointers.
     * @return Vector containing shared_ptr's to all Player's.
     */
    std::vector<std::shared_ptr<Game::Player>> getPlayers();

    /**
     * @brief Returns current amount of rounds.
     * @return Current amount of rounds.
     */
    int getRounds();

    /**
     * @brief Increments actions_.
     */
    void updateActionsCount();

    /**
     * @brief Resets actions_.
     */
    void resetActionsCount();

    /**
     * @brief Converts given ResourceMap resource amounts to be negative.
     * @param to_convert ResourceMap which is to be converted.
     * @return Converted Resourcemap.
     * @post Exception guarantee: Basic
     */
    Course::ResourceMap convertToNegative(Course::ResourceMap to_convert);

    /**
     * @brief Checks whether given tile is owned by the opposing Player.
     * @param tile Tile that is checked.
     * @return True, if other Player owns tile. Else, false.
     * @post Exception guarantee: No-throw.
     */
    bool isOwnedByOtherPlayer(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks whether given tile has MAX_WORKERS.
     * @param tile Tile that is checked.
     * @return True, if MAX_WORKERS reached. Else, false.
     * @post Exception guarantee: No-throw.
     */
    bool hasMaxWorkers(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks whether given tile has MAX_BUILDINGS.
     * @param tile Tile that is checked.
     * @return True, if MAX_BUILDINGS reached. Else, false.
     * @post Exception guarantee: No-throw.
     */
    bool hasMaxBuildings(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks whether MAX_ACTIONS has been reached.
     * @return True, if MAX_ACTIONS reached. Else, false.
     * @post Exception guarantee: No-throw.
     */
    bool isMaxActions();

    /**
     * @brief Checks whether current tile neighbours contain opposing Player's
     * Teekkari.
     * @param GManager ObjectManager
     * @param tile Tile to be checked.
     * @return True, if neighbours contain opposing Player's Teekkari.
     * Else, false.
     * @post Exception guarantee: None
     */
    bool isInTeekkariFightRange(std::shared_ptr<ObjectManager> GManager,
                                std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks whether given tile contains Teekkari.
     * @param tile Tile to be checked.
     * @return True, if tile contains Teekkari. Else, false.
     * @post Exception guarantee: No-throw.
     */
    bool containsTeekkari(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks whether opponents building on current tile
     * can be removed with Teekkari.
     * @param GManager ObjectManager
     * @param tile Tile to be checked
     * @return True, if building can be removed. Else, false.
     * @post Exception guarantee: None.
     */
    bool canRemoveBuilding(std::shared_ptr<ObjectManager> GManager,
                           std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Checks how many workers of given type the Player has in the Game.
     * @param GManager ObjectManager
     * @param worker_type  Worker type to be checked.
     * @return Amount of workers of given type.
     * @post Exception guarantee: No-throw.
     */
    int getPlayersWorkerCount(std::shared_ptr<ObjectManager> GManager,
                              std::string worker_type);

private:

    /**
     * @brief Creates Player objects with given names. Players are stored in
     * players_.
     * @param names Names of Player's to be created.
     * @post Exception guarantee:
     */
    void addPlayers(QList<QString> names);

    /**
     * @brief Sets Player colors. Colors are stored in Player object.
     * @param colors List of Player's colors.
     * @post Exception guarantee:
     */
    void addColors(QList<QColor> colors);

    /**
     * @brief Sets first Player in players_ to be the first in turn.
     * @post Exception guarantee:
     */
    void startGame();

    std::vector<std::shared_ptr<Game::Player>> players_;
    std::shared_ptr<Game::Player> player_in_turn_;
    int rounds_ = 1;
    int actions_ = 0;

};



} // Namespace Game


#endif // GAMEEVENTHANDLER_HH
