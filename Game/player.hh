#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include "core/resourcemaps.h"


const Course::ResourceMap STARTRESOURCES = {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 25},
    {Course::BasicResource::STONE, 50},
    {Course::BasicResource::ORE, 75}
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

private:

    Course::ResourceMap resources_ = {};
};








}



#endif // PLAYER_HH
