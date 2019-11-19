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
    for (std::shared_ptr<Course::TileBase> i : tiles_) {
        if (i->getCoordinate() == coordinate) {
            return i;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    for (std::shared_ptr<Course::TileBase> i : tiles_) {
        if (i->ID == id) {
            return i;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> matching_tiles = {};
    for (std::shared_ptr<Course::TileBase> i : tiles_) {
        for (auto j : coordinates) {
            if (i->getCoordinate() == j) {
                matching_tiles.push_back(i);
            }
        }
    }
    return matching_tiles;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::returnTiles()
{
    return tiles_;
}






} // Namespace Game


