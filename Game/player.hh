#ifndef PLAYER_HH
#define PLAYER_HH

#include <QColor>

#include "core/playerbase.h"
#include "core/gameobject.h"
#include "core/resourcemaps.h"



const Course::ResourceMap STARTRESOURCES = {
    {Course::BasicResource::MONEY, 10000},
    {Course::BasicResource::FOOD, 11000},
    {Course::BasicResource::WOOD, 12000},
    {Course::BasicResource::STONE, 13000},
    {Course::BasicResource::ORE, 14000}
};

namespace Game {

//class TileBase;
//class PlayerBase;
//class GameObject;
//class Coordinate;

// setName
// addObject
// addObjects
// removeObject
// removeObjects (by ID's)
// removeObjects (by GameObject pointers)



class Player : public Course::PlayerBase
{
public:
    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    Course::ResourceMap& getResources();

    void setColor(QColor color);

private:

    Course::ResourceMap resources_ = {};
    QColor player_color_;
};








}



#endif // PLAYER_HH
