#include "gamescene.hh"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Game {

GameScene::GameScene(QWidget* parent, int width, int height, int scale):
    QGraphicsScene(parent),
    m_mapBoundRect(nullptr)
    //m_width(15),
    //m_height(15),
    //m_scale(75)
{
    setSize(width, height);
    setScale(scale);
}

void GameScene::setSize(int width, int height)
{
    if ( width >= SCENE_WIDTH_LIMITS.first && width <= SCENE_WIDTH_LIMITS.second )
    {
        m_width = width;
    }
    if ( height >= SCENE_HEIGHT_LIMITS.first && height <= SCENE_HEIGHT_LIMITS.second )
    {
        m_height = height;
    }
    resize();
}

void GameScene::setScale(int scale)
{
    if ( scale >= SCENE_SCALE_LIMITS.first && scale <= SCENE_SCALE_LIMITS.second )
    {
        m_scale = scale;
    }
    resize();
}

void GameScene::resize()
{
    if ( m_mapBoundRect != nullptr ){
        QGraphicsScene::removeItem(m_mapBoundRect);
    }

    // päätetään että tiedetään mapin koko aina, eli ei lasketa sitä turhaan.
    QRect rect = QRect(m_width-11, m_height-11, (m_width * m_scale)+2, (m_height * m_scale)+2);

    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    m_mapBoundRect = itemAt(rect.topLeft(), QTransform());
    // Draw on the bottom of all items
    m_mapBoundRect->setZValue(-1);
}

int GameScene::getScale() const
{
    return m_scale;
}

std::pair<int, int> GameScene::getSize() const
{
    return {m_width, m_height};
}

void GameScene::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    Course::SimpleMapItem* nItem = new Course::SimpleMapItem(obj, m_scale);
    addItem(nItem);
}

void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            Course::SimpleMapItem* mapitem = static_cast<Course::SimpleMapItem*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }

}

void GameScene::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items();
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : items_list ){
            Course::SimpleMapItem* mapItem = static_cast<Course::SimpleMapItem*>(item);
            if (mapItem->isSameObj(obj)){
                mapItem->updateLoc();
            }
        }
    }
}

bool GameScene::event(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if ( sceneRect().contains(mouse_event->scenePos())){

            QPointF point = mouse_event->scenePos() / m_scale;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            QGraphicsItem* pressed = itemAt(point * m_scale, QTransform());

            if ( pressed == m_mapBoundRect ){
                qDebug() << "Click on map area.";
            }else{
                qDebug() << "ObjID: " <<
                            static_cast<Course::SimpleMapItem*>(pressed)
                            ->getBoundObject()->ID  << " pressed.";
                return true;
            }
        }
    }

    return false;
}




}


