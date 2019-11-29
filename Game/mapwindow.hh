#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

#include "interfaces/igameeventhandler.h"
#include "graphics/simplegamescene.h"
#include "Game_dialogs/startdialog.hh"
#include "Game_dialogs/workerdialog.hh"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "gamescene.hh"
#include "graphics/simplemapitem.h"
#include "mapitem.hh"
#include "core/basicresources.h"
#include "buildings/headquarters.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "Game_buildings/tunitower.hh"
#include "Game_buildings/mine.hh"
#include "workers/basicworker.h"
#include "Game_workers/miner.hh"
#include "Game_workers/teekkari.hh"
#include "exceptions/baseexception.h"
#include "Game_tiles/rock.hh"
#include "Game_tiles/lava.hh"
#include "Game_dialogs/fightdialog.hh"
#include "Game_dialogs/endgamedialog.hh"

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

    void showStartDialog();

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj, QColor player_color = QColor(Qt::black));
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void generateMap();

    void drawMap();

    void addPenalty(std::string info_txt);

    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building);
    void addWorker(const std::shared_ptr<Course::WorkerBase>& worker);
    void removeWorker(const std::shared_ptr<Course::WorkerBase>& worker);

    void initTeekkariFight(bool val);
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

