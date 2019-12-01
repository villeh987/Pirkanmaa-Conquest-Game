#include "mapitem.hh"


namespace Game {

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int size , QColor player_color, std::shared_ptr<ObjectManager> GManager):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()), m_size(size), m_player_color(player_color), GManager(GManager)
{
}

QRectF MapItem::boundingRect() const
{
    // rect of the item
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );


    // calculate the coordinates of the tile
    int tile_x = (m_scenelocation * m_size).x();
    int tile_y = (m_scenelocation * m_size + QPoint(m_size, m_size)).y();

    std::vector<std::shared_ptr<Course::WorkerBase>> workers = GManager->getTile(m_gameobject->getCoordinate())->getWorkers();
    std::vector<std::shared_ptr<Course::BuildingBase> > buildings = GManager->getTile(m_gameobject->getCoordinate())->getBuildings();

    // get the style of the object and draw it
    getStyle(tile_x, tile_y, m_gameobject->getType(), *painter, boundingRect(), m_player_color, workers, buildings);


}

const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject()
{
    return m_gameobject;
}


bool MapItem::isSameGameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

}

