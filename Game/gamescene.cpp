#include "gamescene.hh"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Game {

GameScene::GameScene(QWidget* parent, int width, int height, int scale):
    QGraphicsScene(parent),
    _mapBoundRect(nullptr)

{
    scene_width = width;
    scene_height = height;
    scene_scale = scale;

    QRect game_rect = QRect(-1, -1, (scene_width * scene_scale)+2, (scene_height * scene_scale)+2);

    addRect(game_rect, QPen(Qt::magenta, 10));
    setSceneRect(game_rect);
    _mapBoundRect = itemAt(game_rect.topLeft(), QTransform());

}


void GameScene::drawMapItem(std::shared_ptr<Course::GameObject> obj)
{
    Game::MapItem* nItem = new Game::MapItem(obj, scene_scale);
    addItem(nItem);
}

void GameScene::removeMapItem(std::shared_ptr<Course::GameObject> obj)
{

    QList<QGraphicsItem*> items_list = items();

    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){

            Game::MapItem* mapitem = static_cast<Game::MapItem*>(item);
            //qDebug() << "Mapitem on:" << (mapitem->getBoundObject()->getCoordinate().asQpoint());

            if ( mapitem->isSameObj(obj) ){
                //qDebug() << "poistetaan mapitem:";
                delete mapitem;
            }
        }
    }

}

void GameScene::updateMapItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items();
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : items_list ){
            Game::MapItem* mapItem = static_cast<Game::MapItem*>(item);
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

            QPointF point = mouse_event->scenePos() / scene_scale;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());


            // Paint border rect as highlight

            QGraphicsItem* pressed = itemAt(point * scene_scale, QTransform());


            if ( pressed == _mapBoundRect ){
                qDebug() << "Click on map area.";

            } else if (pressed == highlight_) {
                //qDebug() << "Klikkasit samaa!";
                return true;

            } else {
                if (highlight_ != nullptr) {
                    QGraphicsScene::removeItem(highlight_);
                    delete highlight_;
                }

                highlight_ = this->addRect( QRectF(pressed->boundingRect().x()+2,
                                                   pressed->boundingRect().y()+3,
                                                   pressed->boundingRect().width()-5,
                                                   pressed->boundingRect().height()-5),
                                            QPen(Qt::red, 7));

                //qDebug() << QString::fromStdString(static_cast<Game::MapItem*>(pressed)->getBoundObject()->getType());
                emit tileClicked(static_cast<Game::MapItem*>(pressed)
                                 ->getBoundObject()->getCoordinate());  // Needed to update graphicsView widget

                return true;
            }
        }
    }
    return false;
}



}


