#include "gameeventhandler.hh"
#include "gamescene.hh"
#include <QList>
#include <QDebug>


namespace Game {



GameEventHandler::GameEventHandler()
    :iGameEventHandler()
{

}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{

    for (auto i : players_) {
        if (i->getName() == player->getName()) {

            for (auto& k : i->getResources()) {
                if (k.first == resource) {
                    int result = k.second + amount;
                    if (result < 0) {
                        throw ResourceError("Not enough resources.");
                    } else {
                        k.second += amount;
                    }


                    return true;
                }
            }
        }
    }

    return false;

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    for (auto j : resources) {
        if ( !modifyResource(player, j.first, j.second) ) {
            return false;
        }
    }
    return true;
}

void GameEventHandler::initNewGame(QList<QString> names, QList<QColor> colors)
{
    addPlayers(names);
    addColors(colors);
    startGame();

    qDebug() << "Players added:" << QString::fromStdString(players_.at(0)->getName()) << QString::fromStdString(players_.at(1)->getName());
}

void GameEventHandler::startGame()
{
    player_in_turn_ = players_.at(0);
}

void GameEventHandler::changeTurn()
{
    if (player_in_turn_->getName() == players_.at(0)->getName()) {
        player_in_turn_ = players_.at(1);
    } else {
       player_in_turn_ = players_.at(0);
    }
    ++rounds_;

}

void GameEventHandler::handleGenerateResources(std::vector<std::shared_ptr<Course::TileBase>> tiles)
{
    for (auto i : tiles) {
        if (i->getOwner() == player_in_turn_) {
            i->generateResources();
        }
    }
}

void GameEventHandler::addPlayers(QList<QString> names)

{
    std::string name1 = names.at(0).toStdString();
    std::string name2 = names.at(1).toStdString();

    auto player1 = std::make_shared<Game::Player>(name1);
    auto player2 = std::make_shared<Game::Player>(name2);

    players_.push_back(player1);
    players_.push_back(player2);
}

void GameEventHandler::addColors(QList<QColor> colors)
{
    if (!colors.empty()) {
        players_.at(0)->setColor(colors.at(0));
        players_.at(1)->setColor(colors.at(1));
    }

}

std::shared_ptr<Player> GameEventHandler::getPlayerInTurn()
{
    return player_in_turn_;
}

std::vector<std::shared_ptr<Player> > GameEventHandler::getPlayers()
{
    return players_;
}

int GameEventHandler::getRounds()
{
    return rounds_;
}

void GameEventHandler::updateActionsCount()
{
    ++actions_;
}

void GameEventHandler::resetActionsCount()
{
    actions_ = 0;
}

Course::ResourceMap GameEventHandler::convertToNegative(Course::ResourceMap to_convert)
{
    Course::ResourceMap converted = {};

    for (auto i : to_convert) {
        Course::BasicResource resource = i.first;
        int value = i.second * -1;
        converted.insert(std::pair<Course::BasicResource, int>(resource, value));
    }
    return converted;
}

bool GameEventHandler::isOwnedByOtherPlayer(std::shared_ptr<Course::TileBase> tile)
{

    for (auto i : players_) {
        if (i == tile->getOwner()) {
            if (player_in_turn_ != i) {
                return false;
            }
        }
    }
    return true;
}

bool GameEventHandler::hasMaxWorkers(std::shared_ptr<Course::TileBase> tile)
{
    if (tile->getWorkerCount() == tile->MAX_WORKERS) {
        return true;
    }
    return false;
}

bool GameEventHandler::hasMaxBuildings(std::shared_ptr<Course::TileBase> tile)
{
    if (tile->getBuildingCount() == tile->MAX_BUILDINGS) {
        return true;
    }
    return false;
}

bool GameEventHandler::isMaxActions()
{
    if (actions_ == Game::MAX_ACTIONS) {
        return true;
    }
    return false;
}

bool GameEventHandler::isInTeekkariFightRange(std::shared_ptr<ObjectManager> GManager, std::shared_ptr<Course::TileBase> tile)
{
    std::vector<Course::Coordinate> neighbours = tile->getCoordinate().neighbours();

    if (neighbours.empty()) {
        return false;
    }

    for (auto i : neighbours) {
        if (GManager->getTile(i) != nullptr) {
            if (containsTeekkari(GManager->getTile(i)) && GManager->getTile(i)->getOwner() != player_in_turn_) {
                return true;
            }
        }
    }
    return false;
}

bool GameEventHandler::containsTeekkari(std::shared_ptr<Course::TileBase> tile)
{
    for (auto& i : tile->getWorkers()) {
        if (i->getType() == "Teekkari") {
            return true;
        }
    }
    return false;
}

bool GameEventHandler::canRemoveBuilding(std::shared_ptr<ObjectManager> GManager, std::shared_ptr<Course::TileBase> tile)
{
    std::vector<Course::Coordinate> neighbours = tile->getCoordinate().neighbours();
    for (auto i : neighbours) {
        if (GManager->getTile(i) != nullptr) {
            if (containsTeekkari(GManager->getTile(i)) &&
                    GManager->getTile(i)->getOwner() == player_in_turn_ &&
                    tile->getBuildingCount() > 0) {
                return true;
            }
        }
    }
    return false;
}

int GameEventHandler::getPlayersWorkerCount(std::shared_ptr<ObjectManager> GManager, std::string worker_type)
{
    int count = 0;
    for (auto tile : GManager->returnTiles()) {
        if (tile->getOwner() == player_in_turn_) {
            for (auto worker : tile->getWorkers()) {
                if (worker->getType() == worker_type) {
                    ++count;
                }
            }
        }
    }
    return count;
}


std::vector<std::shared_ptr<Course::WorkerBase> > GameEventHandler::getWagers(std::shared_ptr<ObjectManager> GManager, std::shared_ptr<Course::TileBase> tile)
{
    std::vector<Course::Coordinate> neighbours = tile->getCoordinate().neighbours();
    std::vector<std::shared_ptr<Course::WorkerBase>> wagers = {};

    for (auto w : tile->getWorkers()) {
        if (w->getType() == "Teekkari") {
            wagers.push_back(w);
            break;
        }
    }

    for (auto i : neighbours) {
        if ( containsTeekkari(GManager->getTile(i)) ) {
            for (auto j : GManager->getTile(i)->getWorkers() ) {
                if (j->getType() == "Teekkari") {
                    wagers.push_back(j);
                    break;
                }
            }
        }
    }

    return wagers;
}



}

