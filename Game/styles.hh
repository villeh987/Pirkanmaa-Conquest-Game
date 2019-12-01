#ifndef STYLES_HH
#define STYLES_HH

#include "mapitem.hh"
#include <QPainter>




namespace Game {

/**
     * @brief getStyle creates and gets the graphics for each drawn item
     * @param tile_x the x coordinate of the current tile on the scene
     * @param tile_y the y coordinate of the current tile on the scene
     * @param type of the item to be drawn
     * @param painter ref to the painter created in mapitem class
     * @param boundingRect QRectF the bounding rect of the item
     * @param player_color QColor the players individual color
     * @param workers vector of shared ptrs to the workers on the tile
     * @param buildings vectror of shared ptrs to the buildings on the tile
     */

    void getStyle(int tile_x, int tile_y, std::string type,
                  QPainter& painter, QRectF boundingRect, QColor player_color,
                  std::vector<std::shared_ptr<Course::WorkerBase> > workers,
                  std::vector<std::shared_ptr<Course::BuildingBase>> buildings);

    /**
     * @brief setBoundingRectColor
     * @param tile_x the x coordinate of the current tile on the scene
     * @param tile_y the y coordinate of the current tile on the scene
     * @param player_color QColor the players individual color
     * @param painter ref to the painter created in mapitem class
     * @param boundingRect QRectF the bounding rect of the item
     */
    void setBoundingRectColor(int tile_x, int tile_y, QColor player_color,
                              QPainter& painter, QRectF boundingRect);

    /**
     * @brief drawTree draws the tree
     * @param tile_x the x coordinate of the current tile on the scene
     * @param tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     */
    void drawTree(int tile_x, int tile_y, QPainter& painter);

    /**
     * @brief drawTeekkari
     * @param tile_x tile_x the x coordinate of the current tile on the scene
     * @param tile_y tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     */

    void drawTeekkari(int tile_x, int tile_y, QPainter& painter);

    /**
     * @brief drawTuniTower
     * @param tile_x tile_x the x coordinate of the current tile on the scene
     * @param tile_y tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     */

    void drawTuniTower(int tile_x, int tile_y, QPainter& painter);

    /**
     * @brief drawBasicWorker
     * @param tile_x tile_x the x coordinate of the current tile on the scene
     * @param tile_y tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     * @param boundingRect QRectF the bounding rect of the item
     * @param moving_factor_x int factor that determines the adjust of the x coordinate
     * @param moving_factor_y int factor that determines the adjust of the y coordinate
     */

    void drawBasicWorker(int tile_x, int tile_y, QPainter& painter, QRectF boundingRect,
                         int moving_factor_x, int moving_factor_y);

    /**
     * @brief drawMiner
     * @param tile_x the x coordinate of the current tile on the scene
     * @param tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     */

    void drawMiner(int tile_x, int tile_y, QPainter& painter);

    /**
     * @brief drawRock
     * @param tile_x tile_x the x coordinate of the current tile on the scene
     * @param tile_y the y coordinate of the current tile on the scene
     * @param painter ref to the painter created in mapitem class
     * @param boundingRect QRectF the bounding rect of the item
     */

    void drawRock(int tile_x, int tile_y, QPainter& painter, QRectF boundingRect);
}


#endif // STYLES_HH
