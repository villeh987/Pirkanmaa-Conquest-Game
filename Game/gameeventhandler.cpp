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
                    result = k.second + amount;
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

void GameEventHandler::initNewGame(QList<QString> names)
{
    addPlayers(names);
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

void GameEventHandler::addPlayers(QList<QString> names)

{
    std::string name1 = names.at(0).toStdString();
    std::string name2 = names.at(1).toStdString();

    auto player1 = std::make_shared<Game::Player>(name1);
    auto player2 = std::make_shared<Game::Player>(name2);

    players_.push_back(player1);
    players_.push_back(player2);
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



}

