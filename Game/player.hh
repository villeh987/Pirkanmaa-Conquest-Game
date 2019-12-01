#ifndef PLAYER_HH
#define PLAYER_HH

#include <QColor>

#include "core/playerbase.h"
#include "core/gameobject.h"
#include "core/resourcemaps.h"
#include "constants.hh"



namespace Game {

/**
 * @class Player
 * @brief The Player class is a class used to describe
 * a player in the Game.
 *
 * The class can be used to store and access Player's resources.
 * Expired weak pointers are automatically removed when requesting or removing
 * objects.
 *
 * This class stores Player's resources and also Player's own color in Game.
 *
 * @note Objects are stored as weak pointers.
 */
class Player : public Course::PlayerBase
{
public:

    /**
     * @brief Constructor for the class
     * @param name A std::string for player's name
     * @param objects (optional) A std::vector of shared-pointers to
     * GameObjects.
     */
    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {});


    /**
     * @brief Returns a reference of Player's resources_.
     * @return ResourceMap of Player's resources_.
     * @post Exception Guarantee: No-throw.
     */
    Course::ResourceMap& getResources();

    /**
     * @brief Sets the Player's color.
     * @post Exception Guarantee: No-throw.
     */
    void setColor(QColor color);

    QColor player_color_;

private:
    Course::ResourceMap resources_ = {};
};



} // Namespace Game



#endif // PLAYER_HH
