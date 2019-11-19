#ifndef GAMESCENE_HH
#define GAMESCENE_HH

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"
#include "graphics/simplemapitem.h"

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
     * draws 0,0 (coordinates/the origin) in left upper corner
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     * @param width in tiles for the game map.
     * @param height in tiles for the game map.
     * @param scale is the size in pixels of a single square tile.
     *
     */

    GameScene(QWidget* qt_parent = nullptr,
              int width = 10,
              int height = 10,
              int scale = 50
              );

    /**
     * @brief Default destructor of the class.
     */

    ~GameScene() = default;

    /**
     * @brief get the size of a single tile
     * @return the size of a tile in pixels.
     * @post Exception guarantee: No-throw
     */
    int getSceneScale() const;
    /**
     * @brief draw a new item to the map.
     * @param obj shared ptr to the object
     * @pre obj must have a valid coordinate property.
     * @post Exception guarantee: None
     */
    void drawMapItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief tries to remove drawn object at the location obj points to.
     * If there's multiple objects, will remove the one that matches obj.
     * @param obj shared ptr to the object being deleted.
     * @post Exception guarantee: None
     *
     */
    void removeMapItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief updates the position of obj.
     * @param obj shared ptr to the obj being updated.
     */
    void updateMapItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief simple event handler that notifies when objects or the play
     * area is clicked.
     * @param event that has happened.
     * @return True: if event was  handled in the handler.
     * False: if the event handling was passed over.
     */
    virtual bool event(QEvent* event) override;

private:
    QGraphicsItem* _mapBoundRect;
    int _width;
    int _height;
    int _scale;

};
}

#endif // GAMESCENE_HH
