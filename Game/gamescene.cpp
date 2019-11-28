#include "gamescene.hh"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Game {

GameScene::GameScene(QWidget* parent, int width, int height, int scale, std::shared_ptr<GameEventHandler> s_GEHandler, std::shared_ptr<ObjectManager> GManager):
    QGraphicsScene(parent),
    s_GEHandler(s_GEHandler),
    GManager(GManager)

{
    scene_width_ = width;
    scene_height_ = height;
    scene_scale_ = scale;

    QRect game_rect = QRect(-1, -1, (scene_width_ * scene_scale_)+2, (scene_height_ * scene_scale_)+2);

    addRect(game_rect, QPen(Qt::magenta, 10));
    setSceneRect(game_rect);
}


void GameScene::drawMapItem(std::shared_ptr<Course::GameObject> game_object, QColor player_color)
{
    Game::MapItem* mapitem = new Game::MapItem(game_object, scene_scale_, player_color, GManager);
    addItem(mapitem);
}

void GameScene::removeMapItem(std::shared_ptr<Course::GameObject> game_object)
{

    QList<QGraphicsItem*> scene_items = items();

    if ( scene_items.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : scene_items ){
            Game::MapItem* mapitem = static_cast<Game::MapItem*>(item);
            if ( mapitem->isSameObj(game_object) ){
                delete mapitem;
            }
        }
    }

}

void GameScene::updateMapItem(std::shared_ptr<Course::GameObject> game_object)
{
    QList<QGraphicsItem*> scene_items = items();
    if ( scene_items.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : scene_items ){
            Game::MapItem* mapitem = static_cast<Game::MapItem*>(item);
            if (mapitem->isSameObj(game_object)){
                mapitem->updateLoc();
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

            QPointF point = mouse_event->scenePos() / scene_scale_;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());


            // Paint border rect as highlight

            QGraphicsItem* pressed = itemAt(point * scene_scale_, QTransform());

            if (pressed == highlight_) {
                return true;

            } else {
                if (highlight_ != nullptr) {
                    QGraphicsScene::removeItem(highlight_);
                    delete highlight_;
                    highlight_ = nullptr;
                }

                highlight_ = this->addRect( QRectF(pressed->boundingRect().x()+2,
                                                   pressed->boundingRect().y()+3,
                                                   pressed->boundingRect().width()-5,
                                                   pressed->boundingRect().height()-5),
                                            QPen(s_GEHandler->getPlayerInTurn()->player_color_, 7));
;
                emit tileClicked(static_cast<Game::MapItem*>(pressed)
                                 ->getBoundObject()->getCoordinate());  // Needed to update graphicsView widget

                return true;
            }
        }
    }
    return false;
}

void GameScene::removeHighlight()
{
    if (highlight_ != nullptr) {
        QGraphicsScene::removeItem(highlight_);
        delete highlight_;
        highlight_ = nullptr;
    }
}



} // Namespace Game


