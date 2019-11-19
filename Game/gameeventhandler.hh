#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <memory>
#include <vector>

#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "player.hh"


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

    void initNewGame(QList<QString> names);
    void startGame();
    void changeTurn();

    void addPlayers(QList<QString> names);

    std::shared_ptr<Game::Player> getPlayerInTurn();
    std::vector<std::shared_ptr<Game::Player>> getPlayers();

    int getRounds();

private:
    std::vector<std::shared_ptr<Game::Player>> players_;

    std::shared_ptr<Game::Player> player_in_turn_;
    int rounds_ = 1;

};



} // Namespace Game


#endif // GAMEEVENTHANDLER_HH
