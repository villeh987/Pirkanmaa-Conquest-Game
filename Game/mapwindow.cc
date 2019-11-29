#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include <math.h>
#include <memory>
#include <exception>

#include "graphics/simplemapitem.h"
#include "gamescene.hh"
#include "exceptions/baseexception.h"




MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MapWindow)

{
    ui->setupUi(this);

    // Startdialog

    dialog_ = new StartDialog(this);

    // Manager and handler
    GEHandler = std::make_shared<Game::GameEventHandler>();
    GManager = std::make_shared<Game::ObjectManager>();
    gamescene_ = std::make_shared<Game::GameScene>(this, 10, 10, 50, GEHandler, GManager);

    // End dialog
    end_dialog_ = new EndGameDialog(this, GEHandler, GManager);
    connect(end_dialog_, &EndGameDialog::rejected, this, &MapWindow::close);

    // Random seed
    srand (std::time(NULL));
    rnd_seed_ = rand() % 10000 + 1;
    qDebug() << "Seed:" << qreal(rnd_seed_);

    // Generate map
    generateMap();

    // Connect game buttons
    connect(ui->buildHqButton, &QPushButton::clicked, this, &MapWindow::prepareBuildHq);
    connect(ui->buildFarmButton, &QPushButton::clicked, this, &MapWindow::prepareBuildFarm);
    connect(ui->buildOutpostButton, &QPushButton::clicked, this, &MapWindow::prepareBuildOutpost);
    connect(ui->buildTuniTowerButton, &QPushButton::clicked, this, &MapWindow::prepareBuildTuniTower);
    connect(ui->buildMineButton, &QPushButton::clicked, this, &MapWindow::prepareBuildMine);
    connect(ui->assignWorkerButton, &QPushButton::clicked, this, &MapWindow::showWorkerDialog);
    connect(ui->freeWorkerButton, &QPushButton::clicked, this, &MapWindow::showWorkerDialog);
    connect(ui->teekkariFightButton, &QPushButton::clicked, this, &MapWindow::showFightDialog);
    connect(ui->removeBuildingButton, &QPushButton::clicked, this, &MapWindow::showBuildingDialog);

    // Connect GameWindow signals
    connect(this, &MapWindow::SbuildBuilding, this, &MapWindow::addBuilding);

    // Disable buttons
    ui->teekkariFightButton->setVisible(false);
    ui->removeBuildingButton->setVisible(false);

    // Catch emitted signals from startdialog
    connect(dialog_, &StartDialog::sendLoadData, this, &MapWindow::printData);
    connect(dialog_, &StartDialog::sendNamesAndColors, this, &MapWindow::printNames);
    connect(dialog_, &StartDialog::rejected, this, &MapWindow::close);
    connect(dialog_, &StartDialog::sendNamesAndColors, this, &MapWindow::initNewGame);
    connect(ui->endTurnButton, &QPushButton::clicked, this, &MapWindow::changeTurn);

    // Catch emitted signals from workerDialog
    worker_dialog_ = new WorkerDialog(this, "Choose worker type:");

    connect(worker_dialog_, &WorkerDialog::sendBuildBasicWorker, this, &MapWindow::prepareAddBasicWorker);
    connect(worker_dialog_, &WorkerDialog::sendBuildMiner, this, &MapWindow::prepareAddMiner);
    connect(worker_dialog_, &WorkerDialog::sendBuildTeekkari, this, &MapWindow::prepareAddTeekkari);
    connect(worker_dialog_, &WorkerDialog::sendFreeWorker, this, &MapWindow::prepareRemoveWorker);

    fight_dialog_ = new FightDialog(this);
    // Catch emitted signals from fightDialog
    connect(fight_dialog_, &FightDialog::sendLoser, this, &MapWindow::handleFightResult);
    //connect(fight_dialog_, &FightDialog::sendLoserWager, this, &MapWindow::removeWorker);

    building_dialog_ = new BuildingDialog(this);
    // Catch emitted signals from buildingDialog
    connect(building_dialog_, &BuildingDialog::sendRemoveBuilding, this, &MapWindow::removeBuilding);


    // Connect emitted signal from gamescene
    connect(gamescene_.get(), &Game::GameScene::tileClicked, this, &MapWindow::handleTileclick);

    Game::GameScene* sgs_rawptr = gamescene_.get();
    ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::showStartDialog()
{
    dialog_->open();
}

void MapWindow::drawItem(std::shared_ptr<Course::GameObject> game_object, QColor player_color)
{
    gamescene_->drawMapItem(game_object, player_color);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> game_object)
{
    gamescene_->removeMapItem(game_object);
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> game_object)
{
    gamescene_->updateMapItem(game_object);
}

void MapWindow::generateMap()
{
    Course::WorldGenerator& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(2);
    worldGen.addConstructor<Course::Grassland>(5);
    worldGen.addConstructor<Game::Water>(2);
    worldGen.addConstructor<Game::Rock>(1);
    worldGen.addConstructor<Game::Lava>(1);
    worldGen.generateMap(10, 10, rnd_seed_, GManager, GEHandler);
    drawMap();
}

void MapWindow::drawMap()
{
    for (auto i : GManager->returnTiles()) {
        drawItem(i);
    }
}

void MapWindow::addPenalty(std::string info_txt)
{
    GEHandler->modifyResources( GEHandler->getPlayerInTurn(), Game::GameResourceMaps::PENALTY);
    ui->gameInfoLabel->setText(QString::fromStdString(info_txt));
}

void MapWindow::addBuilding(const std::shared_ptr<Course::BuildingBase>& building)

{
    if (GManager->getTile( active_tile_ )->getType() == "Lava") {
        try {
            addPenalty(Game::PENALTY_BUILD_TEXT);
            updateResourceLabels();
        } catch (Course::BaseException& e) {
            qDebug() << QString::fromStdString(e.msg());
        }

    } else {
        try {
            GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
            GManager->getTile( active_tile_ )->addBuilding(building);

        } catch (Course::BaseException& e) {
                    qDebug() << QString::fromStdString(e.msg());
        }

        try {
            Course::ResourceMap BUILDING_BUILD_COST = GEHandler->convertToNegative(building->BUILD_COST);

            GEHandler->modifyResources(building->getOwner(), BUILDING_BUILD_COST);
            drawItem(building, GEHandler->getPlayerInTurn()->player_color_);
            updateGraphicsView();
            updateResourceLabels();
            disableBuild(GEHandler->hasMaxBuildings(GManager->getTile(active_tile_)));
            disableBuildIndividual();
            updateAndCheckActions();

        } catch (Game::ResourceError& e) {
            qDebug() << QString::fromStdString(e.msg());
            GManager->getTile( active_tile_ )->removeBuilding(building);
            GManager->getTile( active_tile_ )->setOwner(nullptr);
            ui->gameInfoLabel->setText(QString::fromStdString(Game::NOT_ENOUGH_RESOURCES_TEXT));
        }
    }
}

void MapWindow::removeBuilding(const std::shared_ptr<Course::BuildingBase> &building)
{
    try {
        gamescene_->removeMapItem(building);
        updateGraphicsView();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    try {
        qDebug() << "removing building:";
        std::shared_ptr<Course::TileBase> curr_tile = GManager->getTile( active_tile_ );
        curr_tile->removeBuilding(building);
        if ( curr_tile->getWorkerCount() == 0 && curr_tile->getBuildingCount() == 0) {
            curr_tile->setOwner(nullptr);
        }
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    updateAndCheckActions();
    qDebug() << "removed building";
}

void MapWindow::addWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    if (GManager->getTile( active_tile_ )->getType() == "Lava") {
        try {
            addPenalty(Game::PENALTY_ADDWORKER_TEXT);
            updateResourceLabels();
        } catch (Game::ResourceError& e) {
            qDebug() << QString::fromStdString(e.msg());
            ui->gameInfoLabel->setText(QString::fromStdString(Game::NOT_ENOUGH_RESOURCES_TEXT));
        }


    } else {
        try {
            GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
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
            updateAndCheckActions();
            checkForTeekkariFight();

        } catch (Game::ResourceError& e) {
            qDebug() << QString::fromStdString(e.msg());
            GManager->getTile( active_tile_ )->removeWorker(worker);
            GManager->getTile( active_tile_ )->setOwner(nullptr);
            ui->gameInfoLabel->setText(QString::fromStdString(Game::NOT_ENOUGH_RESOURCES_TEXT));
        }
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
        std::shared_ptr<Course::TileBase> curr_tile = GManager->getTile( active_tile_ );
        curr_tile->removeWorker(worker);
        if ( curr_tile->getWorkerCount() == 0 && curr_tile->getBuildingCount() == 0) {
            curr_tile->setOwner(nullptr);
        }
        updateGraphicsView();
        updateResourceLabels();
        updateWorkerCounts();
        disableAssingWorker(GEHandler->hasMaxWorkers(GManager->getTile(active_tile_)));

    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    updateAndCheckActions();
    qDebug() << "removed";
}

void MapWindow::initTeekkariFight(bool val)
{
    //qDebug() << "initTeekkariFight";

    /*if (val) {
        std::vector<std::shared_ptr<Course::WorkerBase>> wagers  =
                GEHandler->getWagers(GManager, GManager->getTile(active_tile_));
        fight_dialog_->setWagers(wagers.at(0), wagers.at(1));
        //qDebug() << "1st wager:" << QString::fromStdString(wagers.at(0)->getOwner()->getName()) <<  "2nd wager:" << QString::fromStdString(wagers.at(1)->getOwner()->getName());
    } */
    ui->teekkariFightButton->setVisible(val);
}

void MapWindow::checkForTeekkariFight()
{
    if (GEHandler->containsTeekkari(GManager->getTile(active_tile_))
            && GEHandler->isInTeekkariFightRange(
                GManager, GManager->getTile(active_tile_))) {
        initTeekkariFight(true);
    } else {
        initTeekkariFight(false);
    }
}

void MapWindow::updateResourceLabels()
{
    ui->moneyValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::MONEY ))));
    ui->foodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::FOOD ))));
    ui->woodValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::WOOD ))));
    ui->stoneValLabel->setText( QString::fromStdString(
                                  std::to_string(
                                  GEHandler->getPlayerInTurn()->getResources()
                                          .at(Course::BasicResource::STONE ))));
    ui->oreValLabel->setText( QString::fromStdString(
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

     ui->workerValLabel->setText(QString::fromStdString(std::to_string(basic_worker_amount)));
     ui->teekkariValLabel->setText(QString::fromStdString(std::to_string(teekkari_amount)));
     ui->minerValLabel->setText(QString::fromStdString(std::to_string(miner_amount)));
}

void MapWindow::updateAndCheckActions()
{
    GEHandler->updateActionsCount();
    if (GEHandler->isMaxActions()) {
        disableGamePanel();
        ui->gameInfoLabel->
                setText(QString::fromStdString(Game::ROUND_MAX_ACTIONS_TEXT));
    }
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
    fight_dialog_->setNames(names.at(0), names.at(1));
    updateResourceLabels();
    ui->turnNameLabel->setText( QString::fromStdString(GEHandler->getPlayerInTurn()->getName()) + "'s turn" );
}

bool MapWindow::gameEnded()
{
    if ( GEHandler->getRounds() >= Game::MAX_ROUDS ) {
        return true;
    } else {
        return false;
    }
}

void MapWindow::endGame()
{
    disableGamePanel();
    end_dialog_->setResults();
    showEndDialog();
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
    ui->turnNameLabel->setText( QString::fromStdString(GEHandler->getPlayerInTurn()->getName()) + "'s turn");
    ui->roundNumberLabel->setText(QString::fromStdString(std::to_string(GEHandler->getRounds())));
    ui->gameInfoLabel->setText(QString::fromStdString(Game::ROUND_START_NOCLICK_TEXT));
    updateResourceLabels();
    disableGamePanel();
    gamescene_->removeHighlight();
    GEHandler->resetActionsCount();
    updateGraphicsView();

    if (gameEnded()) {
        endGame();
    }
}

void MapWindow::disableGamePanel(bool disable)
{
    ui->resourceWidget->setDisabled(disable);
    ui->workerWidget->setDisabled(disable);
    ui->buildWidget->setDisabled(disable);
}

void MapWindow::disableAssingWorker(bool disable)
{
    ui->assignWorkerButton->setDisabled(disable);
}

void MapWindow::disableBuild(bool disable)
{
    ui->buildHqButton->setDisabled(disable);
    ui->buildTuniTowerButton->setDisabled(disable);
    ui->buildMineButton->setDisabled(disable);
    ui->buildFarmButton->setDisabled(disable);
    ui->buildOutpostButton->setDisabled(disable);
    ui->buildSupplyChainButton->setDisabled(disable);
}

void MapWindow::disableBuildIndividual()
{

    if (GManager->getTile(active_tile_)->getBuildings().empty()) {
        disableBuild(false);
    }

    for (auto& i : GManager->getTile(active_tile_)->getBuildings()) {
        std::string type = i->getType();
        if (type == "HeadQuarters") {
            ui->buildHqButton->setDisabled(true);
        }
        if (type == "Outpost") {
            ui->buildOutpostButton->setDisabled(true);
        }

        if (type == "TuniTower") {
            ui->buildTuniTowerButton->setDisabled(true);
        }

        if (type == "Mine") {
            ui->buildMineButton->setDisabled(true);
        }

        if (type == "Farm") {
            ui->buildFarmButton->setDisabled(true);
        }

        if (type == "SupplyChain") {
            ui->buildSupplyChainButton->setDisabled(true);
        }
    }
}

void MapWindow::disableAllButRemoveBuilding(bool disable)
{
    ui->removeBuildingButton->setVisible(disable);
    ui->assignWorkerButton->setDisabled(disable);
    ui->freeWorkerButton->setDisabled(disable);
    ui->workerValLabel->setDisabled(disable);
    ui->workerLabel->setDisabled(disable);
    ui->minerLabel->setDisabled(disable);
    ui->minerValLabel->setDisabled(disable);
    ui->teekkariLabel->setDisabled(disable);
    ui->teekkariValLabel->setDisabled(disable);
    ui->buildWidget->setDisabled(disable);
    ui->resourceWidget->setDisabled(disable);
}

void MapWindow::updateGraphicsView()
{
    ui->graphicsView->viewport()->update();
}

void MapWindow::handleTileclick(Course::Coordinate tile_coords)
{
    if (!GEHandler->isMaxActions()) {
        updateGraphicsView();

        active_tile_ = GManager->getTile(tile_coords)->ID;
        ui->currentTileTypeLabel->setText(QString::fromStdString(GManager->getTile(tile_coords)->getType()));
        ui->gameInfoLabel->setText(QString::fromStdString(Game::ROUND_START_CLICKED_TEXT));

        if (GManager->getTile(active_tile_)->getType() == "Lava") {
             ui->gameInfoLabel->setText(QString::fromStdString(Game::ROUND_LAVA_CLICKED_TEXT));
        }

        // If current tile is dull or owned by other player, disable game actions.
        if (GManager->isDullTile(GManager->getTile(active_tile_)->getType()) ) {
            disableGamePanel(true);
            ui->gameInfoLabel->setText(QString::fromStdString(Game::ROUND_DULL_TILE_CLICKED_TEXT));
        } else if (!(GEHandler->isOwnedByOtherPlayer(GManager->getTile(active_tile_)))) {
            if (checkRemoveBuilding()) {
                initTeekkariFight(false);
                disableGamePanel(false);
                disableAllButRemoveBuilding(true);
            } else {
                disableGamePanel(true);
            }

            ui->gameInfoLabel->setText(QString::fromStdString(Game::ROUND_WRONG_OWNER_TEXT));
        } else {
            disableAllButRemoveBuilding(false);
            disableGamePanel(false);
            disableAssingWorker(GEHandler->hasMaxWorkers(GManager->getTile(active_tile_)));
            disableBuild(GEHandler->hasMaxBuildings(GManager->getTile(active_tile_)));
            disableBuildIndividual();

            checkForTeekkariFight();

        }
        updateWorkerCounts();
    }
}

void MapWindow::prepareBuildHq()
{
    auto hq = std::make_shared<Course::HeadQuarters>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(hq);
}

void MapWindow::prepareBuildFarm()
{
    auto farm = std::make_shared<Course::Farm>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(farm);
}

void MapWindow::prepareBuildOutpost()
{
    auto outpost = std::make_shared<Course::Outpost>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(outpost);
}

void MapWindow::prepareBuildTuniTower()
{
    auto tower = std::make_shared<Game::TuniTower>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(tower);
}

void MapWindow::prepareBuildMine()
{
    auto mine = std::make_shared<Game::Mine>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    emit SbuildBuilding(mine);
}

void MapWindow::showWorkerDialog()
{
    //worker_dialog_ = new WorkerDialog(this, "hello");
    if (sender() == ui->assignWorkerButton) {
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

void MapWindow::showFightDialog()
{
    fight_dialog_->open();
}

void MapWindow::handleFightResult(QString loser)
{
    if (loser == QString::fromStdString(GEHandler->getPlayerInTurn()->getName())) {
        for (auto w : GManager->getTile(active_tile_)->getWorkers()) {
            if (w->getType() == "Teekkari") {
                removeWorker(w);
                break;
            }
        }

    } else {
        std::vector<Course::Coordinate> neighbours = GManager->getTile(active_tile_)->getCoordinate().neighbours();
        for (auto i : neighbours) {
            if ( GEHandler->containsTeekkari(GManager->getTile(i)) ) {
                active_tile_ = GManager->getTile(i)->ID;
                for (auto& j : GManager->getTile(i)->getWorkers() ) {
                    if (j->getType() == "Teekkari") {
                        removeWorker(j);
                        break;
                    }
                }
            }
        }
    }
}

void MapWindow::showEndDialog()
{
    end_dialog_->open();
}

bool MapWindow::checkRemoveBuilding()
{
    if (GEHandler->canRemoveBuilding(GManager, GManager->getTile(active_tile_))) {
        building_dialog_->setTileBuildings(GManager->getTile(active_tile_)->getBuildings());
        ui->removeBuildingButton->setVisible(true);
        return true;
    } else {
        ui->removeBuildingButton->setVisible(false);
        return false;
    }
}

void MapWindow::showBuildingDialog()
{
    building_dialog_->open();
}

void MapWindow::prepareAddBasicWorker()
{
    qDebug() << "prepare to add BasicWorker";
    auto basic_worker = std::make_shared<Course::BasicWorker>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    addWorker(basic_worker);
}

void MapWindow::prepareAddMiner()
{
    qDebug() << "prepare to add Miner";
    auto miner = std::make_shared<Game::Miner>(GEHandler, GManager, GEHandler->getPlayerInTurn());
    //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
    addWorker(miner);
}

void MapWindow::prepareAddTeekkari()
{
    qDebug() << "prepare to add Teekkari";
    if ( GEHandler->getPlayersWorkerCount(GManager, "Teekkari") == Game::MAX_TEEKKARIS_PER_PLAYER) {
        ui->gameInfoLabel->setText(QString::fromStdString(Game::MAX_TEEKKARIS_TEXT));
    } else {
        auto teekkari = std::make_shared<Game::Teekkari>(GEHandler, GManager, GEHandler->getPlayerInTurn());
        //GManager->getTile( active_tile_ )->setOwner( GEHandler->getPlayerInTurn() );
        addWorker(teekkari);
    }
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
