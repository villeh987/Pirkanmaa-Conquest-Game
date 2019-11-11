#include "player.hh"

namespace Game {


Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects)
    :PlayerBase(name, objects)
{

}

Course::ResourceMap Player::getResources() const
{
    return resources_;
}





}


