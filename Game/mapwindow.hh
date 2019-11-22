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
#include "startdialog.hh"
#include "workerdialog.hh"
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
#include "exceptions/baseexception.h"

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

    //void setGEHandler(std::shared_ptr<Course::iGameEventHandler> nHandler);

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void generateMap();

    void drawMap();

    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building);
    void addWorker(const std::shared_ptr<Course::WorkerBase>& worker);
    void removeWorker(const std::shared_ptr<Course::WorkerBase>& worker);

private:
    StartDialog* dialog_ = nullptr;
    WorkerDialog* worker_dialog_ = nullptr;

    Ui::MapWindow* m_ui;

    std::shared_ptr<Game::GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<Game::ObjectManager> m_GManager = nullptr;


    //std::shared_ptr<Course::SimpleGameScene> m_simplescene = nullptr;
    std::shared_ptr<Game::GameScene> m_simplescene = nullptr;

    unsigned int active_tile_;

    void updateResourceLabels();
    void updateWorkerCounts();

    unsigned int rnd_seed_ = 0;



private slots:
    void printData(QString data);
    void printNames(QList<QString> names);

    // Init brand new game
    void initNewGame(QList<QString> names);

    void changeTurn();

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

    void prepareAddBasicWorker();
    void prepareRemoveWorker(std::string worker_type);

signals:
    void SbuildBuilding(const std::shared_ptr<Course::BuildingBase>& building);


};

#endif // MapWINDOW_HH

