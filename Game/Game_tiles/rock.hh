#ifndef ROCK_HH
#define ROCK_HH
#include "tiles/tilebase.h"
#include "Game_resourcemaps/resources.hh"


namespace Game {

/**
 * @brief The Rock class represents Rock in the gameworld.
 *
 * Rock BasicProduction is determined in constants.hh!
 *
 */
class Rock : public Course::TileBase
{
public:

    /**
     * @brief Disabled parameterless constructor.
     */
    Rock() = delete;

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
    Rock(const Course::Coordinate& location,
          const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const unsigned int& max_build = 1,
          const unsigned int& max_work = 3,
          const Course::ResourceMap& production = GameResourceMaps::ROCK_BP
          );

    /**
     * @brief Default destructor.
     */
    virtual ~Rock() = default;

    /**
     * @brief getType Returns a string describing objects type.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const;

};



} // Namespace Game



#endif // ROCK_HH
