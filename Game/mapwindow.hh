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
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "gamescene.hh"
#include "graphics/simplemapitem.h"
#include "mapitem.hh"

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

    void addFarm();

private:
    StartDialog* dialog_ = nullptr;

    Ui::MapWindow* m_ui;

    std::shared_ptr<Game::GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<Game::ObjectManager> m_GManager = nullptr;


    //std::shared_ptr<Course::SimpleGameScene> m_simplescene = nullptr;
    std::shared_ptr<Game::GameScene> m_simplescene = nullptr;

private slots:
    void printData(QString data);
    void printNames(QList<QString> names);


};

#endif // MapWINDOW_HH

