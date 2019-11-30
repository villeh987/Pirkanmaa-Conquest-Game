#include "player.hh"

namespace Game {


Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects)
    :PlayerBase(name, objects),
      resources_(STARTRESOURCES)
{
}

Course::ResourceMap &Player::getResources()
{
    return resources_;
}

void Player::setColor(QColor color)
{
    player_color_ = color;
}


} // Namespace Game


