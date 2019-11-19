#include "mapitem.hh"

namespace Game {

std::map<std::string, QColor> MapItem::c_mapcolors = {};
//std::vector<std::pair<std::string, QColor>> g_vectorcolors = [];

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()), m_size(size)
{
    addNewColor(m_gameobject->getType());
}

QRectF MapItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );

    if (m_gameobject->getType() == "HeadQuarters") {

        QRectF target = boundingRect();
        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("headquarters.png");
        painter->drawPixmap(target, pixmap, source);

    }
    else if (m_gameobject->getType() == "Water") {
         painter->setBrush(QBrush(QColor(Qt::blue)));
         painter->drawRect(boundingRect());


    } else if (m_gameobject->getType() == "Forest") {
        painter->setBrush(QBrush(QColor(0, 102, 0)));
        painter->drawRect(boundingRect());


    } else if (m_gameobject->getType() == "Grassland") {
        painter->setBrush(QBrush(QColor(108, 255, 0)));
        painter->drawRect(boundingRect());


    }
    else {
        painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
        painter->drawRect(boundingRect());
    }

    if ( m_gameobject->getType() == "" ){
        // Draw different types in different shapes <- täytyy selvittää mitä tuo meinaa
    }

}

const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject()
{
    return m_gameobject;
}

void MapItem::updateLoc()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool MapItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

int MapItem::getSize() const
{
    return m_size;
}

void MapItem::setSize(int size)
{
    if ( size > 0 && size <= 500 ){
        m_size = size;
    }
}

void MapItem::addNewColor(std::string type)
{
    // If not found
    if ( c_mapcolors.find(type) == c_mapcolors.end() ){
        std::size_t hash = std::hash<std::string>{}(type);
        c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});

    }


}

}
