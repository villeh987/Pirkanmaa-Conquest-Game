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

    void initNewGame(QList<QString> names, QList<QColor> colors);
    void startGame();
    void changeTurn();
    void handleGenerateResources(std::vector<std::shared_ptr<Course::TileBase> > tiles);

    void addPlayers(QList<QString> names);
    void addColors(QList<QColor> colors);

    std::shared_ptr<Game::Player> getPlayerInTurn();
    std::vector<std::shared_ptr<Game::Player>> getPlayers();

    int getRounds();
    void updateActionsCount();
    void resetActionsCount();

    Course::ResourceMap convertToNegative(Course::ResourceMap to_convert);
    bool isOwnedByOtherPlayer(std::shared_ptr<Course::TileBase> tile);
    bool hasMaxWorkers(std::shared_ptr<Course::TileBase> tile);
    bool hasMaxBuildings(std::shared_ptr<Course::TileBase> tile);
    bool isMaxActions();
    bool isInTeekkariFightRange(std::shared_ptr<ObjectManager> GManager, std::shared_ptr<Course::TileBase> tile);
    bool containsTeekkari(std::shared_ptr<Course::TileBase> tile);
    std::vector<std::shared_ptr<Course::WorkerBase>> getWagers(std::shared_ptr<ObjectManager> GManager, std::shared_ptr<Course::TileBase> tile);

private:
    std::vector<std::shared_ptr<Game::Player>> players_;

    std::shared_ptr<Game::Player> player_in_turn_;
    int rounds_ = 1;
    int actions_ = 0;

};



} // Namespace Game


#endif // GAMEEVENTHANDLER_HH
