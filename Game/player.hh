#ifndef PLAYER_HH
#define PLAYER_HH

#include <QColor>

#include "core/playerbase.h"
#include "core/gameobject.h"
#include "core/resourcemaps.h"
#include "constants.hh"



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
    QColor player_color_;

private:

    Course::ResourceMap resources_ = {};
};








}



#endif // PLAYER_HH
