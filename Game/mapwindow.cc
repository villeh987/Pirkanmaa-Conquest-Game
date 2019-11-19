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

    // Generate map
    generateMap();

    // Connect game buttons
    connect(m_ui->buildHqButton, &QPushButton::clicked, this, &MapWindow::addHq);



    // Catch emitted signals from startdialog
    connect(dialog_, &StartDialog::sendLoadData, this, &MapWindow::printData);
    connect(dialog_, &StartDialog::sendNames, this, &MapWindow::printNames);
    //connect(dialog_, &StartDialog::rejected, this, &MapWindow::close);
    connect(dialog_, &StartDialog::sendNames, this, &MapWindow::initNewGame);
    connect(m_ui->endTurnButton, &QPushButton::clicked, this, &MapWindow::changeTurn);


    // Connect emitted signal from gamescene
    connect(m_simplescene.get(), &Game::GameScene::tileClicked, this, &MapWindow::updateGraphicsView);


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

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::generateMap()
{
    Course::WorldGenerator& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(1);
    worldGen.addConstructor<Course::Grassland>(5);
    worldGen.generateMap(10, 10, 1, m_GManager, m_GEHandler);
    drawMap();

}

void MapWindow::drawMap()
{
    for (auto i : m_GManager->returnTiles()) {
        drawItem(i);
    }
}

void MapWindow::addFarm()
{

}

void MapWindow::addHq()
{
    auto test_hq = std::make_shared<Course::HeadQuarters>(m_GEHandler, m_GManager, m_GEHandler->getPlayerInTurn());
    m_GManager->getTile( m_simplescene->getActiveTile() )->setOwner( m_GEHandler->getPlayerInTurn() );


    try {
        m_GManager->getTile( m_simplescene->getActiveTile() )->addBuilding(test_hq);
    } catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    }

    Course::ResourceMap HQ_BUILD_COST = m_GEHandler->convertToNegative(test_hq->BUILD_COST);
    m_GEHandler->modifyResources(test_hq->getOwner(), HQ_BUILD_COST);
    drawItem(test_hq);
    updateGraphicsView();
    updateResourceLabels();
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



   /* auto test_hq = std::make_shared<Course::HeadQuarters>(m_GEHandler, m_GManager, m_GEHandler->getPlayers().at(0));
    m_GManager->returnTiles().at(0)->setOwner(m_GEHandler->getPlayers().at(0));



    try {
        m_GManager->returnTiles().at(0)->addBuilding(test_hq);

        qDebug() << QString::fromStdString( std::to_string( m_GEHandler->getPlayerInTurn()->getResources().at(Course::BasicResource::MONEY )));
        m_GEHandler->modifyResources(test_hq->getOwner(), test_hq->BUILD_COST);
        qDebug() << QString::fromStdString( std::to_string( m_GEHandler->getPlayerInTurn()->getResources().at(Course::BasicResource::MONEY )));

        drawItem(test_hq);
        m_ui->graphicsView->viewport()->update();
        updateResourceLabels();

    }
    catch (Course::BaseException& e) {
        qDebug() << QString::fromStdString(e.msg());
    } */

   //qDebug() << qreal(m_GManager->returnTiles().at(0)->getBuildingCount());
   //qDebug() <<  QString::fromStdString(m_GManager->returnTiles().at(0)->getBuildings().at(0)->getOwner()->getName());


}

void MapWindow::changeTurn()
{
    m_GEHandler->changeTurn();
    m_ui->turnNameLabel->setText( QString::fromStdString(m_GEHandler->getPlayerInTurn()->getName()) + "'s turn");
    m_ui->roundNumberLabel->setText(QString::fromStdString(std::to_string(m_GEHandler->getRounds())));
    updateResourceLabels();
    //m_ui->graphicsView->viewport()->update();

}

void MapWindow::updateGraphicsView()
{
    m_ui->graphicsView->viewport()->update();
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
