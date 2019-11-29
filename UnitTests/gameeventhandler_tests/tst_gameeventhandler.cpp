#include <QtTest>
#include "gameeventhandler.hh"
#include "constants.hh"
#include "Game_tiles/rock.hh"
// add necessary includes here

class gameeventhandler : public QObject
{
    Q_OBJECT

public:
    gameeventhandler();
    ~gameeventhandler();




private:
    std::unique_ptr<Game::GameEventHandler> test_gehandler;

private slots:
    void test_modifyResourcesAdd();
    void test_modifyResourceAdd();
    void test_modiFyResourceSubtract();
    void test_ModifyResourceResourceError();
    void test_initNewGame();
    void test_changeTurn();
    void test_convertToNegative();

    void cleanup();

};

gameeventhandler::gameeventhandler()
{
    test_gehandler = std::make_unique<Game::GameEventHandler>();

}

gameeventhandler::~gameeventhandler()
{

}

void gameeventhandler::test_modifyResourcesAdd()
{
    Course::ResourceMap tst_resources = {
        {Course::BasicResource::MONEY, 101},
        {Course::BasicResource::FOOD, 102},
        {Course::BasicResource::WOOD, 103},
        {Course::BasicResource::STONE, 104},
        {Course::BasicResource::ORE, 105},
    };

    test_gehandler->addPlayers({"test_player1", "test_player2"});
    QVERIFY(test_gehandler->getPlayers().at(0)->getResources() == Game::STARTRESOURCES);
    test_gehandler->modifyResources(test_gehandler->getPlayers().at(0), tst_resources);
    Course::ResourceMap merged = Course::mergeResourceMaps(tst_resources, Game::STARTRESOURCES);
    QVERIFY2( test_gehandler->getPlayers().at(0)->getResources() == merged, "Resources not equal.");
}

void gameeventhandler::test_modifyResourceAdd()
{
    int value = 6500;
    test_gehandler->addPlayers({"test_player1", "test_player2"});
    QVERIFY(test_gehandler->getPlayers().at(0)->getResources() == Game::STARTRESOURCES);
    test_gehandler->modifyResource(test_gehandler->getPlayers().at(0), Course::BasicResource::MONEY, value);
    QVERIFY2( test_gehandler->getPlayers().at(0)->getResources().
              at(Course::BasicResource::MONEY) ==
              Game::STARTRESOURCES.at(Course::BasicResource::MONEY) + value,
              "Resources not equal.");
}

void gameeventhandler::test_modiFyResourceSubtract()
{
    Course::ResourceMap tst_resources = {
        {Course::BasicResource::MONEY, -11},
        {Course::BasicResource::FOOD, -22},
        {Course::BasicResource::WOOD, -33},
        {Course::BasicResource::STONE, -44},
        {Course::BasicResource::ORE, -55},
    };

    test_gehandler->addPlayers({"test_player1", "test_player2"});
    QVERIFY(test_gehandler->getPlayers().at(0)->getResources() == Game::STARTRESOURCES);
    test_gehandler->modifyResources(test_gehandler->getPlayers().at(0), tst_resources);
    Course::ResourceMap merged = Course::mergeResourceMaps(tst_resources, Game::STARTRESOURCES);
    QVERIFY2( test_gehandler->getPlayers().at(0)->getResources() == merged, "Resources not equal.");
}

void gameeventhandler::test_ModifyResourceResourceError()
{
    Course::ResourceMap tst_resources = {
        {Course::BasicResource::MONEY, -10001},
        {Course::BasicResource::FOOD, 102},
        {Course::BasicResource::WOOD, 103},
        {Course::BasicResource::STONE, 104},
        {Course::BasicResource::ORE, 105},
    };

    test_gehandler->addPlayers({"test_player1", "test_player2"});
    QVERIFY(test_gehandler->getPlayers().at(0)->getResources() == Game::STARTRESOURCES);

    QVERIFY_EXCEPTION_THROWN(test_gehandler->modifyResources
                             (test_gehandler->getPlayers().at(0), tst_resources)
                             , Game::ResourceError);


}

void gameeventhandler::test_initNewGame()
{
    test_gehandler->initNewGame({"test_player1", "test_player2"}, {QColor(Qt::blue), QColor(Qt::green)});
    QVERIFY(test_gehandler->getRounds() == 1);
    QVERIFY(test_gehandler->getPlayers().size() == 2);
    QVERIFY(test_gehandler->getPlayers().at(0)->player_color_ == QColor(Qt::blue));
    QVERIFY(test_gehandler->getPlayers().at(1)->player_color_ == QColor(Qt::green));
    QVERIFY(test_gehandler->getPlayerInTurn()->getName() == "test_player1");

}

void gameeventhandler::test_changeTurn()
{
    test_gehandler->initNewGame({"test_player1", "test_player2"}, {QColor(Qt::blue), QColor(Qt::green)});
    QVERIFY(test_gehandler->getRounds() == 1);
    test_gehandler->changeTurn();
    QVERIFY(test_gehandler->getRounds() == 2);
}

void gameeventhandler::test_convertToNegative()
{
    Course::ResourceMap tst_resourcesPos = {
        {Course::BasicResource::MONEY, 99},
        {Course::BasicResource::FOOD, 98},
        {Course::BasicResource::WOOD, 97},
        {Course::BasicResource::STONE, 96},
        {Course::BasicResource::ORE, 0},
    };

    Course::ResourceMap tst_resourcesNeg = {
        {Course::BasicResource::MONEY, -99},
        {Course::BasicResource::FOOD, -98},
        {Course::BasicResource::WOOD, -97},
        {Course::BasicResource::STONE, -96},
        {Course::BasicResource::ORE, 0},
    };

    QVERIFY2(test_gehandler->convertToNegative(tst_resourcesPos) ==
             tst_resourcesNeg, "Converted resources don't match");
}



void gameeventhandler::cleanup()
{
    test_gehandler = std::make_unique<Game::GameEventHandler>();
}

QTEST_APPLESS_MAIN(gameeventhandler)

#include "tst_gameeventhandler.moc"
