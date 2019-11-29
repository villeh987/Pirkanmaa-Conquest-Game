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

    //void setSize(int width, int height);
    //void setScale(int scale);
    //void resize();

    /**
     * @brief Calls gamescene's drawMapItem.
     * @param game_object A shared pointer to object that is drawn.
     * @param player_color Color with which the object will be highlighted.
     * @post Exception guarantee:
     */
    void drawItem( std::shared_ptr<Course::GameObject> game_object, QColor player_color = QColor(Qt::black));

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

private:
    StartDialog* dialog_ = nullptr;
    EndGameDialog* end_dialog_ = nullptr;
    WorkerDialog* worker_dialog_ = nullptr;
    FightDialog* fight_dialog_ = nullptr;

    Ui::MapWindow* ui;

    std::shared_ptr<Game::GameEventHandler> GEHandler = nullptr;
    std::shared_ptr<Game::ObjectManager> GManager = nullptr;
    std::shared_ptr<Game::GameScene> gamescene_ = nullptr;

    unsigned int active_tile_;

    void updateResourceLabels();
    void updateWorkerCounts();
    void updateAndCheckActions();

    unsigned int rnd_seed_ = 0;


private slots:
    void printData(QString data);
    void printNames(QList<QString> names, QList<QColor> colors);

    // Init brand new game
    void initNewGame(QList<QString> names, QList<QColor> colors);

    bool gameEnded();
    void endGame();

    void changeTurn();
    void disableGamePanel(bool disable = true);
    void disableAssingWorker(bool disable = true);
    void disableBuild(bool disable = true);
    void disableBuildIndividual();

    // Init loaded game
    //void initLoadedGame(QString data);

    // Update GraphicsView
    void updateGraphicsView();

    void handleTileclick(Course::Coordinate tile_coords);

    void prepareBuildHq();
    void prepareBuildFarm();
    void prepareBuildOutpost();
    void prepareBuildTuniTower();
    void prepareBuildMine();

    // Worker Dialog
    void showWorkerDialog();
    void destroyWorkerDialog();

    // Fight dialog
    void showFightDialog();
    void handleFightResult(QString loser);

    // End dialog

    void showEndDialog();

    void prepareAddBasicWorker();
    void prepareAddMiner();
    void prepareAddTeekkari();
    void prepareRemoveWorker(std::string worker_type);

signals:
    void SbuildBuilding(const std::shared_ptr<Course::BuildingBase>& building);


};

#endif // MapWINDOW_HH

