#include <QtTest>
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "Game_tiles/rock.hh"
#include "Game_tiles/water.hh"

// add necessary includes here

class objectmanager : public QObject
{
    Q_OBJECT

public:
    objectmanager();
    ~objectmanager();

    std::shared_ptr<Game::GameEventHandler> test_gehandler;
    std::shared_ptr<Game::ObjectManager> test_objectmanager;

private slots:
    void test_addTiles();
    void test_getTile();
    void test_getTileNotFound();
    void test_getTiles();
    void test_getTilesNotFound();
    void test_getTilesEmptyCoords();
    void test_returnTiles();
    void test_isDullTile();

    void cleanup();

};

objectmanager::objectmanager()
{
    test_gehandler = std::make_shared<Game::GameEventHandler>();
    test_objectmanager = std::make_shared<Game::ObjectManager>();
}

objectmanager::~objectmanager()
{
}

void objectmanager::test_addTiles()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(0, 0),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(Course::Coordinate(1, 1),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY( test_objectmanager->getTile(Course::Coordinate(0, 0)) == test_tile1 );
    QVERIFY( test_objectmanager->getTile(Course::Coordinate(1, 1)) == test_tile2 );
}

void objectmanager::test_getTile()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(3, 4),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(Course::Coordinate(4, 3),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY( test_objectmanager->getTile(Course::Coordinate(3, 4)) == test_tile1 );
    QVERIFY( test_objectmanager->getTile(Course::Coordinate(4, 3)) == test_tile2 );

    QVERIFY( test_objectmanager->getTile(test_tile1->ID) == test_tile1 );
    QVERIFY( test_objectmanager->getTile(test_tile2->ID) == test_tile2 );
}

void objectmanager::test_getTileNotFound()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(3, 4),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    test_objectmanager->addTiles(tiles);

    QVERIFY( test_objectmanager->getTile(Course::Coordinate(3, 4)) == test_tile1 );
    QVERIFY( test_objectmanager->getTile(Course::Coordinate(6, 6)) == nullptr );
    QVERIFY( test_objectmanager->getTile(12345) == nullptr );
}

void objectmanager::test_getTiles()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    std::vector<Course::Coordinate> coords =
    { Course::Coordinate(5, 5), Course::Coordinate(2, 6) };

    auto test_tile1 = std::make_shared<Game::Rock>(coords.at(0),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(coords.at(1),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY(test_objectmanager->getTiles(coords) == tiles);
}

void objectmanager::test_getTilesNotFound()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    std::vector<Course::Coordinate> coords = {Course::Coordinate(5, 5),
                                              Course::Coordinate(2, 6)};

    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(5, 9),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(Course::Coordinate(8, 8),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY( test_objectmanager->getTiles(coords).empty() );
}

void objectmanager::test_getTilesEmptyCoords()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    std::vector<Course::Coordinate> coords = {};

    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(4, 1),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(Course::Coordinate(9, 9),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY( test_objectmanager->getTiles(coords).empty() );
}

void objectmanager::test_returnTiles()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    auto test_tile1 = std::make_shared<Game::Rock>(Course::Coordinate(0, 4),
                                                   test_gehandler,
                                                   test_objectmanager);
    auto test_tile2 = std::make_shared<Game::Water>(Course::Coordinate(4, 8),
                                                   test_gehandler,
                                                   test_objectmanager);
    tiles.push_back(test_tile1);
    tiles.push_back(test_tile2);

    test_objectmanager->addTiles(tiles);

    QVERIFY(test_objectmanager->returnTiles() == tiles);
}

void objectmanager::test_isDullTile()
{
    auto test_tile1 = std::make_shared<Game::Water>(Course::Coordinate(4, 8),
                                                   test_gehandler,
                                                   test_objectmanager);

    auto test_tile2 = std::make_shared<Game::Rock>(Course::Coordinate(0, 4),
                                                   test_gehandler,
                                                   test_objectmanager);

    QVERIFY( test_objectmanager->isDullTile( test_tile1->getType() ) );
    QVERIFY( !test_objectmanager->isDullTile( test_tile2->getType() ) );
}

void objectmanager::cleanup()
{
    test_gehandler = std::make_shared<Game::GameEventHandler>();
    test_objectmanager = std::make_shared<Game::ObjectManager>();
}

QTEST_APPLESS_MAIN(objectmanager)

#include "tst_objectmanager.moc"
