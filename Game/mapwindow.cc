#include "mapwindow.hh"
#include "ui_mapwindow.h"


#include "graphics/simplemapitem.h"
#include "gamescene.hh"
#include "exceptions/baseexception.h"


#include <math.h>
#include <memory>
#include <exception>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    //m_simplescene(new Course::SimpleGameScene(this)) //tänne
    m_simplescene(new Game::GameScene(this))
{
    m_ui->setupUi(this);

    // Startdialog

    dialog_ = new StartDialog(this);

    // Manager and handler
    m_GEHandler = std::make_shared<Game::GameEventHandler>();
    m_GManager = std::make_shared<Game::ObjectManager>();

    // Random seed
    srand (std::time(NULL));
    rnd_seed_ = rand() % 10000 + 1;
    qDebug() << "Seed:" << qreal(rnd_seed_);

    // Generate map
    generateMap();

    // Connect game buttons

    connect(m_ui->buildHqButton, &QPushButton::clicked, this, &MapWindow::prepareBuildHq);
    connect(m_ui->buildFarmButton, &QPushButton::clicked, this, &MapWindow::prepareBuildFarm);
    connect(m_ui->buildOutpostButton, &QPushButton::clicked, this, &MapWindow::prepareBuildOutpost);
    connect(m_ui->buildTuniTowerButton, &QPushButton::clicked, this, &MapWindow::prepareBuildTuniTower);
    connect(m_ui->buildMineButton, &QPushButton::clicked, this, &MapWindow::prepareBuildMine);

    connect(m_ui->assignWorkerButton, &QPushButton::clicked, this, &MapWindow::showWorkerDialog);
    connect(m_ui->freeWorkerButton, &QPushButton::clicked, this, &MapWindow::showWorkerDialog);

    connect(this, &MapWindow::SbuildBuilding, this, &MapWindow::addBuilding);


    // Catch emitted signals from startdialog

    connect(dialog_, &StartDialog::sendLoadData, this, &MapWindow::printData);
    connect(dialog_, &StartDialog::sendNames, this, &MapWindow::printNames);
    //connect(dialog_, &StartDialog::rejected, this, &MapWindow::close);
    connect(dialog_, &StartDialog::sendNames, this, &MapWindow::initNewGame);
    connect(m_ui->endTurnButton, &QPushButton::clicked, this, &MapWindow::changeTurn);

    // Catch emitted signals from workerDialog

    worker_dialog_ = new WorkerDialog(this, "Choose worker type:");

    connect(worker_dialog_, &WorkerDialog::sendBuildBasicWorker, this, &MapWindow::prepareAddBasicWorker);
    connect(worker_dialog_, &WorkerDialog::sendFreeWorker, this, &MapWindow::prepareRemoveWorker);
    //connect(worker_dialog_, &WorkerDialog::accepted, this, &MapWindow::destroyWorkerDialog);
    //connect(worker_dialog_, &WorkerDialog::rejected, this, &MapWindow::destroyWorkerDialog);

    // Connect emitted signal from gamescene
    connect(m_simplescene.get(), &Game::GameScene::tileClicked, this, &MapWindow::handleTileclick);


    //Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();
    Game::GameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));


}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::showStartDialog()
{
    dialog_->open();
}

/*void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
} */
/*
void MapWindow::setSize(int width, int height)
{
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
}
*/
void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateMapItem(obj);
}

void MapWindow::generateMap()
{
    Course::WorldGenerator& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(2);
    worldGen.addConstructor<Course::Grassland>(5);
    worldGen.addConstructor<Game::Water>(2);
    worldGen.generateMap(10, 10, rnd_seed_, m_GManager, m_GEHandler);
    drawMap();

}

void MapWindow::drawMap()
{
    for (auto i : m_GManager->returnTiles()) {
        drawItem(i);
    }
}

void MapWindow::addBuilding(const std::shared_ptr<Course::BuildingBase>& building)

{
    try {
        m_GManager->getTile( active_tile_ )->addBuilding(building);
    } catch (Game::ResourceError& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    Course::ResourceMap BUILDING_BUILD_COST = m_GEHandler->convertToNegative(building->BUILD_COST);
    try {
        m_GEHandler->modifyResources(building->getOwner(), BUILDING_BUILD_COST);
        drawItem(building);
        updateGraphicsView();
        updateResourceLabels();

    } catch (Game::ResourceError& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::addWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    try {
        m_GManager->getTile( active_tile_ )->addWorker(worker);
    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    Course::ResourceMap WORKER_RECRUITMENT_COST = m_GEHandler->convertToNegative(worker->RECRUITMENT_COST);
    try {
        m_GEHandler->modifyResources(worker->getOwner(), WORKER_RECRUITMENT_COST);
        drawItem(worker);
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::removeWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    try {
        m_simplescene->removeMapItem(worker);
        updateGraphicsView();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    try {
        qDebug() << "removing:";
        m_GManager->getTile( active_tile_ )->removeWorker(worker);
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::updateResourceLabels()
{
    m_ui->moneyValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  m_GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::MONEY ))));
    m_ui->foodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  m_GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::FOOD ))));
    m_ui->woodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  m_GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::WOOD ))));
    m_ui->stoneValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  m_GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::STONE ))));
    m_ui->oreValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  m_GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::ORE ))));
}

void MapWindow::updateWorkerCounts()
{
    std::vector<std::shared_ptr<Course::WorkerBase>> tile_workers = m_GManager->getTile(active_tile_)->getWorkers();
    int basic_worker_amount = 0;



    for (auto& worker: tile_workers) {
        if (worker->getType() == "BasicWorker") {
           ++basic_worker_amount;
        }
    }

     m_ui->workerValLabel->setText(QString::fromStdString(std::to_string(basic_worker_amount)));


}

void MapWindow::printData(QString data)
{
    qDebug() << data;
}

void MapWindow::printNames(QList<QString> names)
{
    qDebug() << names;
}

void MapWindow::initNewGame(QList<QString> names)
{
    m_GEHandler->initNewGame(names);
    updateResourceLabels();
    m_ui->turnNameLabel->setText( QString::fromStdString(m_GEHandler->getPlayerInTurn()->getName()) + "'s turn" );
}

void MapWindow::changeTurn()
{
    m_GEHandler->changeTurn();
    m_ui->turnNameLabel->setText( QString::fromStdString(m_GEHandler->getPlayerInTurn()->getName()) + "'s turn");
    m_ui->roundNumberLabel->setText(QString::fromStdString(std::to_string(m_GEHandler->getRounds())));
    updateResourceLabels();
    m_simplescene->removeHighlight();
    updateGraphicsView();

}

void MapWindow::updateGraphicsView()
{
    m_ui->graphicsView->viewport()->update();

}

void MapWindow::handleTileclick(Course::Coordinate tile_coords)
{
    updateGraphicsView();

    /*qDebug() << qreal(m_GManager->getTile(tile_coords)->ID)
             << qreal(m_GManager->getTile(tile_coords)->getCoordinate().x())
             << qreal(m_GManager->getTile(tile_coords)->getCoordinate().y()); */

    active_tile_ = m_GManager->getTile(tile_coords)->ID;
    updateWorkerCounts();

}

void MapWindow::prepareBuildHq()
{
    auto hq = std::make_shared<Course::HeadQuarters>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(hq);
}

void MapWindow::prepareBuildFarm()
{
    auto farm = std::make_shared<Course::Farm>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(farm);
}

void MapWindow::prepareBuildOutpost()
{
    auto outpost = std::make_shared<Course::Outpost>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(outpost);
}

void MapWindow::prepareBuildTuniTower()
{
    auto tower = std::make_shared<Game::TuniTower>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(tower);
}

void MapWindow::prepareBuildMine()
{
    auto mine = std::make_shared<Game::Mine>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(mine);
}

void MapWindow::showWorkerDialog()
{
    //worker_dialog_ = new WorkerDialog(this, "hello");
    if (sender() == m_ui->assignWorkerButton) {
        worker_dialog_->setInfoText("Choose worker type:");
    } else {
        worker_dialog_->setInfoText("Choose worker type to free:");
    }
    worker_dialog_->open();
}

void MapWindow::destroyWorkerDialog()
{
    delete worker_dialog_;
}

void MapWindow::prepareAddBasicWorker()
{
    qDebug() << "prepare to add BasicWorker";
    auto basic_worker = std::make_shared<Course::BasicWorker>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( active_tile_ )->setOwner( m_GEHandler->getPlayerInTurn() );
    addWorker(basic_worker);
}

void MapWindow::prepareRemoveWorker(std::string worker_type)
{
    qDebug() << "prepare to remove BasicWorker";
    for (auto& worker : m_GManager->getTile( active_tile_ )->getWorkers()) {
        if (worker->getType() == worker_type) {
            removeWorker(worker);
            break;
        }
    }

}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeMapItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawMapItem(obj);
}

