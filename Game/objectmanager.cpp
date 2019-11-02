#include "objectmanager.hh"
namespace Game {


ObjectManager::ObjectManager()
    :Course::iObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    tiles_ = tiles;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{

}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{

}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{

}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::returnTiles()
{
    return tiles_;
}






} // Namespace Game


