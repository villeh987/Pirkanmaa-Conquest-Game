#ifndef LAVA_HH
#define LAVA_HH

#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {

/**
 * @brief The Lava class represents Lava in the gameworld.
 *
 * Lava doesn't have BasicProduction, since it's Lava and it cannot be built on.
 * Player's trying to build or add workers on Lava will get resource penalty.
 *
 */
class Lava : public Course::TileBase
{
public:

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the GameEventHandler.
     * @param objectmanager points to the ObjectManager.
     * @param max_build (Optional) How many buildings can be added on the tile.
     * @param max_work (Optional) How many workers can be added on the tile.
     * @param production (Optional) What resources does the tile generate.
     *
     * @note Max build, max work are overriden by other means in the game.
     * @note LAVA_BP is empty, since it cannot be owned nor built on.
     */
    Lava(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 1,
         const Course::ResourceMap& production = GameResourceMaps::LAVA_BP);


    /**
     * @brief getType Returns a string describing objects type.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const override;

};



} // Namespace Game




#endif // LAVA_HH
