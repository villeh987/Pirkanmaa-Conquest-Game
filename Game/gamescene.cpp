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
    Game::MapItem* nItem = new Game::MapItem(obj, m_scale);
    addItem(nItem);
}

void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            Game::MapItem* mapitem = static_cast<Game::MapItem*>(item);
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

            QPointF point = mouse_event->scenePos() / m_scale;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            // Paint border rect as highlight



            QGraphicsItem* pressed = itemAt(point * m_scale, QTransform());

            //QRectF current = static_cast<Course::SimpleMapItem*>(pressed)
             //       ->boundingRect();

            //QRectF current_compare = QRectF(current.x()+5,  current.y()+5, current.width()-10, current.height()-10);

            //qDebug() << "curr_x:" << qreal(current.x()) << "curr_y:" << qreal(current.y()) << "curr_width:" << qreal(current.width()) << "curr_height:" << qreal(current.height());
            //qDebug() << "prev_x:" << qreal(previous_.x()) << "prev_y:" << qreal(previous_.y())<< "prev_width:" << qreal(previous_.width()) << "prev_height:" << qreal(previous_.height());
            //qDebug() << "comp_x:" << qreal(current_compare.x()) << "comp_y:" << qreal(current_compare.y()) << "comp_width:" << qreal(current_compare.width()) << "comp_height:" << qreal(current_compare.height());


            if ( pressed == m_mapBoundRect ){
                qDebug() << "Click on map area.";

            } else if (pressed == highlight_) {
                //qDebug() << "Klikkasit samaa!";

                return true;

            } else if (highlight_ == nullptr) {
                qDebug() << "ObjID: " <<
                            static_cast<Game::MapItem*>(pressed)
                            ->getBoundObject()->ID  << " pressed.";

                //QRectF highlight = pressed->boundingRect();
                highlight_ = this->addRect(pressed->boundingRect(), QPen(Qt::red, 10));
                emit tileClicked();
                active_tile_ =  static_cast<Game::MapItem*>(pressed)
                        ->getBoundObject()->ID;
                //previous_ = current;
                return true;

            } else {
                //qDebug() << "Ny vaihetaa paikkaa!";
                QGraphicsScene::removeItem(highlight_);
                delete highlight_;
                highlight_ = this->addRect(pressed->boundingRect(), QPen(Qt::red, 10));
                //previous_ = current_compare;
                emit tileClicked();

                active_tile_ =  static_cast<Game::MapItem*>(pressed)
                        ->getBoundObject()->ID;

                return true;
            }


        }
    }
    return false;


}

unsigned int GameScene::getActiveTile()
{
    return active_tile_;
}




}


