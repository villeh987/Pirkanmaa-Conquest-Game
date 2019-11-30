#ifndef WATER_HH
#define WATER_HH
#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"

namespace Game {

/**
 * @brief The Water class represents Water in the gameworld.
 *
 * @note Water is a dull tile, that means no actions may be performed on it!
 *
 */

class Water : public Course::TileBase
{
public:

    /**
     * @brief Disabled parameterless constructor.
     */
    Water() = delete;

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
     */
    Water(const Course::Coordinate& location,
          const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const unsigned int& max_build = 0,
          const unsigned int& max_work = 0,
          const Course::ResourceMap& production = GameResourceMaps::WATER_BP
          );

    /**
     * @brief Default destructor.
     */
    virtual ~Water() = default;

    /**
     * @brief getType Returns a string describing objects type.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const override;


};

} // Namespace Game



#endif // WATER_HH
