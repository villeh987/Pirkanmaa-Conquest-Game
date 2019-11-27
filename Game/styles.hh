#ifndef STYLES_HH
#define STYLES_HH

#include "mapitem.hh"
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>



namespace Game {

   void getStyle(int tile_x, int tile_y, std::string type, QPainter& painter, QRectF boundingRect, QColor player_color);
   void setBoundingRectColor(int tile_x, int tile_y, QColor player_color, QPainter& painter, QRectF boundingRect);
   void drawTree(int tile_x, int tile_y, QPainter& painter);
}


#endif // STYLES_HH
