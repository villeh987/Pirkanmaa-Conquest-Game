#ifndef GAMESCENE_HH
#define GAMESCENE_HH

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"
#include "graphics/simplemapitem.h"
#include "tiles/tilebase.h"
#include "mapitem.hh"
#include "Game_tiles/water.hh"
#include "gameeventhandler.hh"

namespace Game {


/**
 * @brief The GameScene class is a custom QgraphicsScene that shows
 * the rendering of the game map.
 */
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the class.
     *
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     * @param width in tiles for the game map.
     * @param height in tiles for the game map.
     * @param scale is the size in pixels of a single square tile.
     *
     */

    GameScene(QWidget* qt_parent = nullptr,
              int width = 10,
              int height = 10,
              int scale = 50,
              std::shared_ptr<GameEventHandler> s_GEHandler = nullptr
              );

    /**
     * @brief Default destructor of the class.
     */

    ~GameScene() = default;

    /**
     * @brief draw a new item to the map.
     * @param obj shared ptr to the object
     * @pre obj must have a valid coordinate property.
     * @post Exception guarantee: None
     */
    void drawMapItem(std::shared_ptr<Course::GameObject> game_object, QColor player_color);

    /**
     * @brief tries to remove drawn object at the location obj points to.
     * If there's multiple objects, will remove the one that matches obj.
     * @param obj shared ptr to the object being deleted.
     * @post Exception guarantee: None
     *
     */
    void removeMapItem(std::shared_ptr<Course::GameObject> game_object);

    /**
     * @brief updates the position of obj.
     * @param obj shared ptr to the obj being updated.
     */
    void updateMapItem(std::shared_ptr<Course::GameObject> game_object);

    /**
     * @brief simple event handler that notifies when objects or the play
     * area is clicked.
     * @param event that has happened.
     * @return True: if event was  handled in the handler.
     * False: if the event handling was passed over.
     */
    virtual bool event(QEvent* event) override;

    void removeHighlight();


private:
    QGraphicsRectItem* highlight_ = nullptr;

    int scene_width_;
    int scene_height_;
    int scene_scale_;

    std::shared_ptr<GameEventHandler> s_GEHandler;

signals:
    void tileClicked(Course::Coordinate tile_coords);


};
}

#endif // GAMESCENE_HH
