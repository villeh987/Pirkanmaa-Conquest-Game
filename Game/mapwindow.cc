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
    m_ui(new Ui::MapWindow)

{
    m_ui->setupUi(this);

    // Startdialog

    dialog_ = new StartDialog(this);

    // Manager and handler
    GEHandler = std::make_shared<Game::GameEventHandler>();
    GManager = std::make_shared<Game::ObjectManager>();
    gamescene_ = std::make_shared<Game::GameScene>(this, 10, 10, 50, GEHandler);

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
    connect(dialog_, &StartDialog::sendNamesAndColors, this, &MapWindow::printNames);
    connect(dialog_, &StartDialog::rejected, this, &MapWindow::close);
    connect(dialog_, &StartDialog::sendNamesAndColors, this, &MapWindow::initNewGame);
    connect(m_ui->endTurnButton, &QPushButton::clicked, this, &MapWindow::changeTurn);

    // Catch emitted signals from workerDialog

    worker_dialog_ = new WorkerDialog(this, "Choose worker type:");

    connect(worker_dialog_, &WorkerDialog::sendBuildBasicWorker, this, &MapWindow::prepareAddBasicWorker);
    connect(worker_dialog_, &WorkerDialog::sendBuildMiner, this, &MapWindow::prepareAddMiner);
    connect(worker_dialog_, &WorkerDialog::sendBuildTeekkari, this, &MapWindow::prepareAddTeekkari);
    connect(worker_dialog_, &WorkerDialog::sendFreeWorker, this, &MapWindow::prepareRemoveWorker);

    // Connect emitted signal from gamescene
    connect(gamescene_.get(), &Game::GameScene::tileClicked, this, &MapWindow::handleTileclick);


    //Course::SimpleGameScene* sgs_rawptr = gamescene_.get();
    Game::GameScene* sgs_rawptr = gamescene_.get();

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
    GEHandler = nHandler;
} */
/*
void MapWindow::setSize(int width, int height)
{
    gamescene_->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    gamescene_->setScale(scale);
}

void MapWindow::resize()
{
    gamescene_->resize();
}
*/
void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    gamescene_->updateMapItem(obj);
}

void MapWindow::generateMap()
{
    Course::WorldGenerator& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(2);
    worldGen.addConstructor<Course::Grassland>(5);
    worldGen.addConstructor<Game::Water>(2);
    worldGen.addConstructor<Game::Rock>(1);
    worldGen.generateMap(10, 10, rnd_seed_, GManager, GEHandler);
    drawMap();

}

void MapWindow::drawMap()
{
    for (auto i : GManager->returnTiles()) {
        drawItem(i);
    }
}

void MapWindow::addBuilding(const std::shared_ptr<Course::BuildingBase>& building)

{
    try {
        GManager->getTile( active_tile_ )->addBuilding(building);
    } catch (Game::ResourceError& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    Course::ResourceMap BUILDING_BUILD_COST = GEHandler->convertToNegative(building->BUILD_COST);
    try {
        GEHandler->modifyResources(building->getOwner(), BUILDING_BUILD_COST);
        drawItem(building, GEHandler->getPlayerInTurn()->player_color_);
        updateGraphicsView();
        updateResourceLabels();
        disableBuild(GEHandler->hasMaxBuildings(GManager->getTile(active_tile_)));
        disableBuildIndividual();

    } catch (Game::ResourceError& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::addWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    try {
        GManager->getTile( active_tile_ )->addWorker(worker);
    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    Course::ResourceMap WORKER_RECRUITMENT_COST = GEHandler->convertToNegative(worker->RECRUITMENT_COST);
    try {
        GEHandler->modifyResources(worker->getOwner(), WORKER_RECRUITMENT_COST);
        drawItem(worker, GEHandler->getPlayerInTurn()->player_color_);
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();
        disableAssingWorker(GEHandler->hasMaxWorkers(GManager->getTile(active_tile_)));

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::removeWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    try {
        gamescene_->removeMapItem(worker);
        updateGraphicsView();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    try {
        qDebug() << "removing:";
        GManager->getTile( active_tile_ )->removeWorker(worker);
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();
        disableAssingWorker(GEHandler->hasMaxWorkers(GManager->getTile(active_tile_)));

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }
}

void MapWindow::updateResourceLabels()
{
    m_ui->moneyValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::MONEY ))));
    m_ui->foodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::FOOD ))));
    m_ui->woodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::WOOD ))));
    m_ui->stoneValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::STONE ))));
    m_ui->oreValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::ORE ))));
}

void MapWindow::updateWorkerCounts()
{
    std::vector<std::shared_ptr<Course::WorkerBase>> tile_workers = GManager->getTile(active_tile_)->getWorkers();
    int basic_worker_amount = 0;
    int miner_amount = 0;
    int teekkari_amount = 0;



    for (auto& worker: tile_workers) {
        if (worker->getType() == "BasicWorker") {
           ++basic_worker_amount;
        } else if (worker->getType() == "Miner") {
            ++miner_amount;
        } else if (worker->getType() == "Teekkari") {
            ++teekkari_amount;
        }
    }

     m_ui->workerValLabel->setText(QString::fromStdString(std::to_string(basic_worker_amount)));
     m_ui->teekkariValLabel->setText(QString::fromStdString(std::to_string(teekkari_amount)));
     m_ui->minerValLabel->setText(QString::fromStdString(std::to_string(miner_amount)));


}

void MapWindow::printData(QString data)
{
    qDebug() << data;
}

void MapWindow::printNames(QList<QString> names, QList<QColor> colors)
{
    qDebug() << names;
    qDebug() << "Player1 color:" << colors.at(0);
    qDebug() << "Player1 color:" << colors.at(1);
}

void MapWindow::initNewGame(QList<QString> names, QList<QColor> colors)
{
    GEHandler->initNewGame(names, colors);
    updateResourceLabels();
    m_ui->turnNameLabel->setText( QString::fromStdString(GEHandler->getPlayerInTurn()->getName()) + "'s turn" );
}

void MapWindow::changeTurn()
{
    try {
        GEHandler->handleGenerateResources(GManager->returnTiles());

      // If this error is thrown, it means that player doesn't have enough resources to proceed the game
    } catch (Game::ResourceError& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    GEHandler->changeTurn();
    m_ui->turnNameLabel->setText( QString::fromStdString(GEHandler->getPlayerInTurn()->getName()) + "'s turn");
    m_ui->roundNumberLabel->setText(QString::fromStdString(std::to_string(GEHandler->getRounds())));
    updateResourceLabels();
    disableGamePanel();
    gamescene_->removeHighlight();
    updateGraphicsView();

}

void MapWindow::disableGamePanel(bool disable)
{
    m_ui->resourceWidget->setDisabled(disable);
    m_ui->workerWidget->setDisabled(disable);
    m_ui->buildWidget->setDisabled(disable);

}

void MapWindow::disableAssingWorker(bool disable)
{
    m_ui->assignWorkerButton->setDisabled(disable);
}

void MapWindow::disableBuild(bool disable)
{
    m_ui->buildHqButton->setDisabled(disable);
    m_ui->buildTuniTowerButton->setDisabled(disable);
    m_ui->buildMineButton->setDisabled(disable);
    m_ui->buildFarmButton->setDisabled(disable);
    m_ui->buildOutpostButton->setDisabled(disable);
    m_ui->buildSupplyChainButton->setDisabled(disable);

    //m_ui->buildWidget->setDisabled(disable);
}

void MapWindow::disableBuildIndividual()
{

    if (GManager->getTile(active_tile_)->getBuildings().empty()) {
        disableBuild(false);
    }

    for (auto& i : GManager->getTile(active_tile_)->getBuildings()) {
        std::string type = i->getType();
        if (type == "HeadQuarters") {
            m_ui->buildHqButton->setDisabled(true);
        }
        if (type == "Outpost") {
            m_ui->buildOutpostButton->setDisabled(true);
        }

        if (type == "TuniTower") {
            m_ui->buildTuniTowerButton->setDisabled(true);
        }

        if (type == "Mine") {
            m_ui->buildMineButton->setDisabled(true);
        }

        if (type == "Farm") {
            m_ui->buildFarmButton->setDisabled(true);
        }

        if (type == "SupplyChain") {
            m_ui->buildSupplyChainButton->setDisabled(true);
        }





        /*
        m_ui->buildHqButton->setDisabled(type == "HeadQuarters");
        m_ui->buildTuniTowerButton->setDisabled(type == "TuniTower");
        m_ui->buildMineButton->setDisabled(type == "Mine");
        m_ui->buildFarmButton->setDisabled(type == "Farm");
        m_ui->buildOutpostButton->setDisabled(type == "Outpost");
        m_ui->buildSupplyChainButton->setDisabled(type == "SupplyChain"); */
     }
}

void MapWindow::updateGraphicsView()
{
    m_ui->graphicsView->viewport()->update();

}

void MapWindow::handleTileclick(Course::Coordinate tile_coords)
{
    updateGraphicsView();

    /*qDebug() << qreal(GManager->getTile(tile_coords)->ID)
             << qreal(GManager->getTile(tile_coords)->getCoordinate().x())
             << qreal(GManager->getTile(tile_coords)->getCoordinate().y()); */

    active_tile_ = GManager->getTile(tile_coords)->ID;

    // If current tile is dull or owned by other player, disable game actions.
    if (GManager->isDullTile(GManager->getTile(active_tile_)->getType()) ) {
        disableGamePanel(true);
    } else if (!(GEHandler->isOwnedByOtherPlayer(GManager->getTile(active_tile_)))) {
        disableGamePanel(true);
    } else {
        disableGamePanel(false);
        disableAssingWorker(GEHandler->hasMaxWorkers(GManager->getTile(active_tile_)));
        disableBuild(GEHandler->hasMaxBuildings(GManager->getTile(active_tile_)));
        disableBuildIndividual();

    }
    updateWorkerCounts();

}

void MapWindow::prepareBuildHq()
{
    auto hq = std::make_shared<Course::HeadQuarters>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(hq);
}

void MapWindow::prepareBuildFarm()
{
    auto farm = std::make_shared<Course::Farm>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(farm);
}

void MapWindow::prepareBuildOutpost()
{
    auto outpost = std::make_shared<Course::Outpost>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(outpost);
}

void MapWindow::prepareBuildTuniTower()
{
    auto tower = std::make_shared<Game::TuniTower>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(tower);
}

void MapWindow::prepareBuildMine()
{
    auto mine = std::make_shared<Game::Mine>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
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
    auto basic_worker = std::make_shared<Course::BasicWorker>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    addWorker(basic_worker);
}

void MapWindow::prepareAddMiner()
{
    qDebug() << "prepare to add Miner";
    auto miner = std::make_shared<Game::Miner>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    addWorker(miner);
}

void MapWindow::prepareAddTeekkari()
{
    qDebug() << "prepare to add Teekkari";
    auto teekkari = std::make_shared<Game::Teekkari>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    addWorker(teekkari);
}

void MapWindow::prepareRemoveWorker(std::string worker_type)
{
    qDebug() << "prepare to remove BasicWorker";
    for (auto& worker : GManager->getTile( active_tile_ )->getWorkers()) {
        if (worker->getType() == worker_type) {
            removeWorker(worker);
            break;
        }
    }
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    gamescene_->removeMapItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj, QColor player_color)
{
    gamescene_->drawMapItem(obj, player_color);
}

