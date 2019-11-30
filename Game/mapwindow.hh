#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

#include "buildings/headquarters.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "core/basicresources.h"
#include "core/worldgenerator.h"
#include "exceptions/baseexception.h"
#include "interfaces/igameeventhandler.h"
#include "graphics/simplegamescene.h"
#include "graphics/simplemapitem.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "workers/basicworker.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "gamescene.hh"
#include "mapitem.hh"
#include "Game_buildings/tunitower.hh"
#include "Game_buildings/mine.hh"
#include "Game_workers/miner.hh"
#include "Game_workers/teekkari.hh"
#include "Game_tiles/rock.hh"
#include "Game_tiles/lava.hh"
#include "Game_dialogs/fightdialog.hh"
#include "Game_dialogs/endgamedialog.hh"
#include "Game_dialogs/startdialog.hh"
#include "Game_dialogs/workerdialog.hh"
#include "Game_dialogs/buildingdialog.hh"

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

    /**
     * @brief Displays StartDialog
     */
    void showStartDialog();


private:

    /**
     * @brief Calls gamescene's drawMapItem.
     * @param game_object A shared pointer to object that is drawn.
     * @param player_color Color with which the object will be highlighted.
     * @post Exception guarantee:
     */
    void drawItem( std::shared_ptr<Course::GameObject> game_object,
                   QColor player_color = QColor(Qt::black));

    /**
     * @brief Calls gamescene's removeMapItem.
     * @param game_object A shared pointer to object that is removed.
     * @post Exception guarantee:
     */
    void removeItem( std::shared_ptr<Course::GameObject> game_object);

    /**
     * @brief Calls gamescene's updateMapItem.
     * @param game_object A shared pointer to object that is updated.
     * @post Exception guarantee:
     */
    void updateItem( std::shared_ptr<Course::GameObject> game_object);

    /**
     * @brief Generates tiles using wordGenerator based on rnd_seed_.
     * Creates instance of worldGenerator, adds constructors by tile type and
     * calls worldGenerator's generateMap.
     * Calls drawMap to draw generated tiles.
     * @post Exception guarantee:
     */
    void generateMap();

    /**
     * @brief Calls drawItem for earch tile from ObjectManager.
     * @post Exception guarantee:
     */
    void drawMap();

    /**
     * @brief Modifies the current Player's resources by amount PENALTY.
     * @param info_txt Text displayed to current Player.
     * @post Exception guarantee:
     */
    void addPenalty(std::string info_txt);

    /**
     * @brief Adds the given building to current active tile.
     * Adds penalty in case Player tries to build on Lava.
     * Sets ownership of current tile to current Player.
     * Modifies Player's resources according to BUILD_COST.
     * Calls drawItem to add building to gamescene.
     * Updates UI resource and worker labels.
     * Handles ResourceErrors in case when Player doesn't have enough resources.
     * @param building A shared pointer to building to be added.
     * @post Exception guarantee:
     * @exception
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building);


    /**
     * @brief Removes the given building from current active tile.
     * If tile contains no buildings and workers,
     * removes ownership of current tile from current Player.
     * Calls drawItem to remove building from gamescene.
     * Updates UI resource and worker labels.
     * @param building A shared pointer to building to be removed.
     * @post Exception guarantee:
     * @exception
     */
    void removeBuilding(const std::shared_ptr<Course::BuildingBase>& building);

    /**
     * @brief Adds the given worker to current active tile.
     * Adds penalty in case Player tries to add on Lava.
     * Sets ownership of current tile to current Player.
     * Modifies Player's resources according to RECRUITMENT_COST.
     * Calls drawItem to add worker to gamescene.
     * Updates UI resource and worker labels.
     * Checks for TeekkariFight.
     * Handles ResourceErrors in case when Player doesn't have enough resources.
     * @param worker A shared pointer to worker to be added.
     * @post Exception guarantee:
     * @exception
     */
    void addWorker(const std::shared_ptr<Course::WorkerBase>& worker);

    /**
     * @brief Removes the given worker from current active tile.
     * If tile contains no buildings,
     * removes ownership of current tile from current Player.
     * Calls drawItem to remove worker from gamescene.
     * Updates UI resource and worker labels.
     * @param worker A shared pointer to worker to be removed.
     * @post Exception guarantee:
     * @exception
     */
    void removeWorker(const std::shared_ptr<Course::WorkerBase>& worker);

    /**
     * @brief Sets teekkariFightButton visibility according to val.
     * @param val If true, sets button visible, if false, sets invisible.
     */
    void initTeekkariFight(bool val);

    /**
     * @brief Checks from GameEventHandler whether current active tile contains
     * Teekkari, and whether the opposing Player has a Teekkari
     * as a neighbour to current active tile.
     * If the above conditions are met, sets teekkariFightButton to be visible.
     */
    void checkForTeekkariFight();

    /**
     * @brief Updates UI resource labels according to
     * player_in_turn_(In GEHandler).
     */
    void updateResourceLabels();

    /**
     * @brief Updates UI worker counts according to current active_tile_.
     */
    void updateWorkerCounts();

    /**
     * @brief Updates actions count (In GEHandler) and checks
     * whether max allowrd amount of actions per round has been reached.
     * Updates game info label accordingly.
     */
    void updateAndCheckActions();

    StartDialog* dialog_ = nullptr;
    EndGameDialog* end_dialog_ = nullptr;
    WorkerDialog* worker_dialog_ = nullptr;
    FightDialog* fight_dialog_ = nullptr;
    BuildingDialog* building_dialog_ = nullptr;

    Ui::MapWindow* ui;

    std::shared_ptr<Game::GameEventHandler> GEHandler = nullptr;
    std::shared_ptr<Game::ObjectManager> GManager = nullptr;
    std::shared_ptr<Game::GameScene> gamescene_ = nullptr;

    unsigned int active_tile_;
    unsigned int rnd_seed_ = 0;


private slots:

    // Init brand new game
    /**
     * @brief Receives Player names and colors from StartDialog and
     * sends them to GEHandler. Also sets Player names in fight_dialog_.
     * Updates resource labels and sets first Player to be first in turn.
     * @param names List of Player names.
     * @param colors List of Player colors.
     */
    void initNewGame(QList<QString> names, QList<QColor> colors);

    /**
     * @brief Checks if MAX_ROUNDS has been reached.
     * @return Return true if MAX_ROUNDS has been reached.
     * Else, return false.
     */
    bool gameEnded();

    /**
     * @brief Disables game actions, sets final results in end_dialog_
     * and displays end_dialog_.
     */
    void endGame();

    /**
     * @brief Handles all events that happen when Player clicks "End Turn".
     * - Calls GEHandlers method to generate resources based on tile- and
     * workeractions.
     * - Calls GEHanders changeTurn.
     * - Updates current Player name to be shown in UI.
     * - Updates current round to be shown in UI.
     * - Updates UI resourcelabels to show current player resources.
     * - Disables game actions until tile is clicked.
     * - Removes highlight from gamescene until tile is clicked.
     * - Resets actions count.
     * - Calls gameEnded
     */
    void changeTurn();

    /**
     * @brief Disables game actions.
     * @param disable If true, disable. If false, enable.
     */
    void disableGamePanel(bool disable = true);

    /**
     * @brief Disables worker assignment.
     * @param disable If true, disable. If false, enable.
     */
    void disableAssingWorker(bool disable = true);

    /**
     * @brief Disables build.
     * @param disable If true, disable. If false, enable.
     */
    void disableBuild(bool disable = true);

    /**
     * @brief Makes sure that only one bulding of the same type
     * may exist on one tile.
     * Disables build option, if building already exists on tile.
     */
    void disableBuildIndividual();

    /**
     * @brief Disables all game actions, but Destroy button.
     * Needed, when Player clicks opposing Player's tile while having
     * own Teekkari next to it.
     * @param disable If true, disable. If false, enable.
     */
    void disableAllButRemoveBuilding(bool disable = true);

    // Init loaded game
    //void initLoadedGame(QString data);

    /**
     * @brief Updates graphicsView widget's viewport.
     */
    void updateGraphicsView();

    /**
     * @brief Handles all actions when a tile is clicked.
     * - Check if max actions is reached (GEHandler).
     * - Sets clicked tile as active_tile_
     * - Updates tile type label in UI.
     * - Update game info text, which varies depending on tile type
     * and tile ownership.
     * - Check if tile is dull (cannot perform any actions).
     * - Enable Destroy button if Player has Teekkari next to
     * opposing Player's building.
     * -Enable Teekkarifight, if Player has Teekkari next to
     * opposing Player's Teekkari.
     * @param tile_coords Coordinates of clicked tile.
     */
    void handleTileclick(Course::Coordinate tile_coords);

    /**
     * @brief Prepare to build HeadQuarters.
     * Creates new HeadQuarters shared_ptr and emits signal to build it.
     * Called when build Headquarters button is clicked.
     */
    void prepareBuildHq();

    /**
     * @brief Prepare to build Farm.
     * Creates new Farm shared_ptr and emits signal to build it.
     * Called when build Farm button is clicked.
     */
    void prepareBuildFarm();

    /**
     * @brief Prepare to build Outpost.
     * Creates new Outpost shared_ptr and emits signal to build it.
     * Called when build Outpost button is clicked.
     */
    void prepareBuildOutpost();

    /**
     * @brief Prepare to build TuniTower.
     * Creates new TuniTower shared_ptr and emits signal to build it.
     * Called when build TuniTower button is clicked.
     */
    void prepareBuildTuniTower();

    /**
     * @brief Prepare to build Mine.
     * Creates new Mine shared_ptr and emits signal to build it.
     * Called when build Mine button is clicked.
     */
    void prepareBuildMine();


    /**
     * @brief Opens worker_dialog_.
     */
    void showWorkerDialog();



    /**
     * @brief Opens fight_dialog_.
     */
    void showFightDialog();

    /**
     * @brief Removes Teekkari from the Player that lost the Teekkarifight.
     * @param loser Name of Player that lost the fight.
     */
    void handleFightResult(QString loser);

    /**
     * @brief Opens end_dialog_.
     */
    void showEndDialog();

    /**
     * @brief Check from GEHandler whether building can be removed.
     * If it can be removed, enable Destroy button in UI.
     * @return True, if building can be removed. Else, false.
     */
    bool checkRemoveBuilding();

    /**
     * @brief Opens building_dialog_. Called when Destroy button is clicked.
     */
    void showBuildingDialog();

    /**
     * @brief Prepare to add BasicWorker.
     * Creates new BasicWorker shared_ptr and calls addWorker.
     * Called by signal from worker_dialog_.
     */
    void prepareAddBasicWorker();

    /**
     * @brief Prepare to add Miner.
     * Creates new Miner shared_ptr and calls addWorker.
     * Called by signal from worker_dialog_.
     */
    void prepareAddMiner();

    /**
     * @brief Prepare to add Teekkari.
     * Creates new Teekkari shared_ptr and calls addWorker.
     * Called by signal from worker_dialog_.
     */
    void prepareAddTeekkari();

    /**
     * @brief Prepare to remove any worker.
     * Calls removeWorker.
     * Called by signal from worker_dialog_.
     * @param worker_type Type of worker to be removed.
     */
    void prepareRemoveWorker(std::string worker_type);

signals:

    /**
     * @brief Signal for addBuilding
     * Emitted from prepare building methods.
     * @param building Building to be added.
     */
    void SbuildBuilding(const std::shared_ptr<Course::BuildingBase>& building);


};

#endif // MapWINDOW_HH

