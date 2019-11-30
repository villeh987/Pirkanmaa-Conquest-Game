#ifndef MAPITEM_HH
#define MAPITEM_HH


#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include <memory>
#include <map>

#include "core/gameobject.h"
#include "gameeventhandler.hh"
#include "styles.hh"

namespace Game {

/**
 * @brief The mapitem class is a custon QGraphicsitem that
 * acts as a singe Gameobject's graphical element.
 */
class MapItem : public QGraphicsItem
{
public:

    /**
     * @brief Constructor
     * @param obj shared_ptr to the obj.
     * @param size of the created item in pixels.
     * @param player_color the color of the player.
     * @param GManager shared ptr to the object manager.
     * @pre obj must have a valid Coordinate.
     */
    MapItem(const std::shared_ptr<Course::GameObject> &obj, int size, QColor player_color, std::shared_ptr<ObjectManager> GManager);

    /**
     * @brief boundingRect
     * @return the bounding rectangle of current item.
     */
    QRectF boundingRect() const override;

    /**
     * @brief paints the item
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /**
     * @brief getBoundObject
     * @return the object this item is bound to.
     */
    const std::shared_ptr<Course::GameObject> &getBoundObject();


    /**
     * @brief checks if this instance has obj as bound obj.
     * @param obj to compare to.
     * @return True: if obj is pointing to the same object as this item.
     * False otherwise.
     */
    bool isSameGameObj(std::shared_ptr<Course::GameObject> obj);

    /*
    /**
     * @brief getSize
     * @return size of the object in pixels.
     * @post Exception guarantee: No-throw

    int getObjectSize() const;
    */

    /*
    /**
     * @brief setSize
     * @param size of the object in pixels.
     * @post Exception guarantee: No-throw

    void setObjectSize(int size);
    */


private:
    const std::shared_ptr<Course::GameObject> m_gameobject;
    QPoint m_scenelocation;
    int m_size;
    QColor m_player_color;

    //static std::map<std::string, QColor> c_mapcolors;
    //static std::vector<std::pair<std::string, QColor>> g_vectorcolors;

    std::shared_ptr<ObjectManager> GManager;

};

}



#endif // MAPITEM_HH
