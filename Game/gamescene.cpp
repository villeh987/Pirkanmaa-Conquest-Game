#include "gamescene.hh"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Game {

GameScene::GameScene(QWidget* parent, int width, int height, int scale):
    QGraphicsScene(parent),
    _mapBoundRect(nullptr)

{
    _width = width;
    _height = height;
    _scale = scale;
    QRect rect = QRect(-1, -1, (_width * _scale)+2, (_height * _scale)+2);
    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    _mapBoundRect = itemAt(rect.topLeft(), QTransform());

}

int GameScene::getSceneScale() const
{
    return _scale;
}

void GameScene::drawMapItem(std::shared_ptr<Course::GameObject> obj)
{
    Course::SimpleMapItem* newItem = new Course::SimpleMapItem(obj, _scale);
    addItem(newItem);
}

void GameScene::removeMapItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> map_items_list = items(obj->getCoordinate().asQpoint());
    if ( map_items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : map_items_list ){
            Course::SimpleMapItem* mapitem = static_cast<Course::SimpleMapItem*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }

}

void GameScene::updateMapItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> map_items_list = items();
    if ( map_items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : map_items_list ){
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

            QPointF point = mouse_event->scenePos() / _scale;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            QGraphicsItem* pressed = itemAt(point * _scale, QTransform());

            if ( pressed == _mapBoundRect ){
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


