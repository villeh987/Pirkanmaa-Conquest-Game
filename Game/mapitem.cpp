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

    } else if (m_gameobject->getType() == "Farm") {
        QRectF target = boundingRect();
        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("farm.png");
        painter->drawPixmap(target, pixmap, source);

    } else if (m_gameobject->getType() == "Outpost") {
        QRectF target = boundingRect();
        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("outpost.png");
        painter->drawPixmap(target, pixmap, source);

    } else if (m_gameobject->getType() == "Mine") {
        QRectF target = boundingRect();
        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("mine.png");
        painter->drawPixmap(target, pixmap, source);

    } else if (m_gameobject->getType() == "Water") {
         painter->setBrush(QBrush(QColor(Qt::blue)));
         painter->drawRect(boundingRect());


    } else if (m_gameobject->getType() == "Forest") {
        painter->setBrush(QBrush(QColor(0, 102, 0)));
        painter->drawRect(boundingRect());

        int tile_x = (m_scenelocation * m_size).x();
        int tile_y = (m_scenelocation * m_size + QPoint(m_size, m_size)).y();


        QPointF tree_trunk[5] = {
            QPointF(tile_x+4.2,tile_y-37),
            QPointF(tile_x+4.2,tile_y-40),
            QPointF(tile_x+5.8,tile_y-40),
            QPointF(tile_x+5.8,tile_y-37),
            QPointF(tile_x+4.2,tile_y-37)

        };

        QBrush tree_trunk_brush = QColor(102, 50, 0);
        QPen tree_trunk_pen = QPen(QColor(102, 50, 0));

        QPointF tree_leaves_left[8] = {
            QPointF(tile_x+5, tile_y-41),
            QPointF(tile_x+1, tile_y-40),
            QPointF(tile_x+5, tile_y-44),
            QPointF(tile_x+1.5, tile_y-43), // tää kans
            QPointF(tile_x+5, tile_y-47),
            QPointF(tile_x+3, tile_y-47),
            QPointF(tile_x+5, tile_y-49),
            QPointF(tile_x+5, tile_y-41)

        };

        QPointF tree_leaves_right[8] = {
            QPointF(tile_x+5, tile_y-41),
            QPointF(tile_x+9, tile_y-40),
            QPointF(tile_x+5, tile_y-44),
            QPointF(tile_x+8.5, tile_y-43),//tää
            QPointF(tile_x+5, tile_y-47),
            QPointF(tile_x+7, tile_y-47),
            QPointF(tile_x+5, tile_y-49),
            QPointF(tile_x+5, tile_y-41)

        };



        QPen tree_leaves_pen = QPen(QColor(128, 255, 0));
        QBrush tree_leaves_brush = QColor(128, 255, 0);

        painter->setBrush(tree_leaves_brush);
        painter->setPen(tree_leaves_pen);
        //int horizontal_count = 0;
        //while (horizontal_count <= 5){
            // tähän tulee looppi joka piirtää ruudun täyteen puita
        //}

        painter->drawPolygon(tree_leaves_left, 8);
        painter->drawPolygon(tree_leaves_right, 8);

        painter->setBrush(tree_trunk_brush);
        painter->setPen(tree_trunk_pen);


        painter->drawPolygon(tree_trunk, 5);



    } else if (m_gameobject->getType() == "Grassland") {
        painter->setBrush(QBrush(QColor(108, 255, 0)));
        painter->drawRect(boundingRect());


    } else if (m_gameobject->getType() == "TuniTower") {


        int tile_x = (m_scenelocation * m_size).x();
        int tile_y = (m_scenelocation * m_size + QPoint(m_size, m_size)).y();

        painter->setBrush(QBrush(QColor(204, 102, 0)));
        QPointF tuni_tower[4] = {
            QPointF(tile_x + 12, tile_y - 40),
            QPointF(tile_x + 12, tile_y),
            QPointF(tile_x + 38, tile_y),
            QPointF(tile_x + 38, tile_y - 40)
        };

        QPointF tuni_forehead[9] = {
            QPointF(tile_x+17, tile_y-25),
            QPointF(tile_x+17, tile_y-30),
            QPointF(tile_x+20, tile_y-35),
            QPointF(tile_x+25, tile_y-37),
            QPointF(tile_x+25, tile_y-35),
            QPointF(tile_x+20, tile_y-32),
            QPointF(tile_x+19, tile_y-30),
            QPointF(tile_x+19, tile_y-25),
            QPointF(tile_x+17, tile_y-25)
        };

        QPointF tuni_right_eye[5] = {
            QPointF(tile_x+20.5, tile_y-25),
            QPointF(tile_x+20.5, tile_y-27),
            QPointF(tile_x+24, tile_y-27),
            QPointF(tile_x+24, tile_y-25),
            QPointF(tile_x+20.5, tile_y-25)
        };

        QPointF tuni_left_eye[7] = {
            QPointF(tile_x+25, tile_y-20),
            QPointF(tile_x+25, tile_y-27),
            QPointF(tile_x+32, tile_y-27),
            QPointF(tile_x+32, tile_y-25),
            QPointF(tile_x+27, tile_y-25),
            QPointF(tile_x+27, tile_y-20),
            QPointF(tile_x+25, tile_y-20)
        };

        QPointF tuni_cheeck[12] = {
            QPointF(tile_x+25, tile_y-15),
            QPointF(tile_x+30, tile_y-16),
            QPointF(tile_x+33, tile_y-20),
            QPointF(tile_x+33, tile_y-25),
            QPointF(tile_x+35, tile_y-25),
            QPointF(tile_x+35, tile_y-19),
            QPointF(tile_x+35, tile_y-19),
            QPointF(tile_x+32, tile_y-17),
            QPointF(tile_x+32, tile_y-15),
            QPointF(tile_x+29, tile_y-14),
            QPointF(tile_x+25, tile_y-14),
            QPointF(tile_x+25, tile_y-15)


        };

        QBrush tuni_face_brush;
        tuni_face_brush.setColor(QColor(Qt::white));
        tuni_face_brush.setStyle(Qt::SolidPattern);


        const QPen tuni_pen(Qt::black, 1, Qt::SolidLine);

        painter->setPen(tuni_pen);
        painter->drawPolygon(tuni_tower, 4);

        painter->setBrush(tuni_face_brush);

        painter->drawPolygon(tuni_forehead, 9);
        painter->drawPolygon(tuni_right_eye, 5);
        painter->drawPolygon(tuni_left_eye, 7);
        painter->drawPolygon(tuni_cheeck, 12);



    }

    else if (m_gameobject->getType() == "BasicWorker") {

        int tile_x = (m_scenelocation * m_size).x();
        int tile_y = (m_scenelocation * m_size + QPoint(m_size, m_size)).y();


        QPointF tuni_forehead[9] = {
            QPointF(tile_x+17, tile_y-25),
            QPointF(tile_x+17, tile_y-30),
            QPointF(tile_x+20, tile_y-35),
            QPointF(tile_x+25, tile_y-37),
            QPointF(tile_x+25, tile_y-35),
            QPointF(tile_x+20, tile_y-32),
            QPointF(tile_x+19, tile_y-30),
            QPointF(tile_x+19, tile_y-25),
            QPointF(tile_x+17, tile_y-25)
        };

        QPointF tuni_right_eye[5] = {
            QPointF(tile_x+20.5, tile_y-25),
            QPointF(tile_x+20.5, tile_y-27),
            QPointF(tile_x+24, tile_y-27),
            QPointF(tile_x+24, tile_y-25),
            QPointF(tile_x+20.5, tile_y-25)
        };

        QPointF tuni_left_eye[7] = {
            QPointF(tile_x+25, tile_y-20),
            QPointF(tile_x+25, tile_y-27),
            QPointF(tile_x+32, tile_y-27),
            QPointF(tile_x+32, tile_y-25),
            QPointF(tile_x+27, tile_y-25),
            QPointF(tile_x+27, tile_y-20),
            QPointF(tile_x+25, tile_y-20)
        };

        QPointF tuni_cheeck[12] = {
            QPointF(tile_x+25, tile_y-15),
            QPointF(tile_x+30, tile_y-16),
            QPointF(tile_x+33, tile_y-20),
            QPointF(tile_x+33, tile_y-25),
            QPointF(tile_x+35, tile_y-25),
            QPointF(tile_x+35, tile_y-19),
            QPointF(tile_x+35, tile_y-19),
            QPointF(tile_x+32, tile_y-17),
            QPointF(tile_x+32, tile_y-15),
            QPointF(tile_x+29, tile_y-14),
            QPointF(tile_x+25, tile_y-14),
            QPointF(tile_x+25, tile_y-15)


        };

        QBrush tuni_face_brush;
        tuni_face_brush.setColor(QColor(Qt::blue));
        tuni_face_brush.setStyle(Qt::SolidPattern);


        const QPen tuni_pen(Qt::white, 0.7, Qt::SolidLine);

        painter->setPen(tuni_pen);

        painter->setBrush(tuni_face_brush);

        painter->drawPolygon(tuni_forehead, 9);
        painter->drawPolygon(tuni_right_eye, 5);
        painter->drawPolygon(tuni_left_eye, 7);
        painter->drawPolygon(tuni_cheeck, 12);

        QRectF target = boundingRect();
        QRectF source(-300, 10, 1100, 1100);
        QPixmap pixmap("workerhelmet.png");
        painter->drawPixmap(target, pixmap, source);

        QRectF target2 = boundingRect();
        QRectF source2(-200, -400, 800, 800);
        QPixmap pixmap2("cigarette.png");
        painter->drawPixmap(target2, pixmap2, source2);
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
