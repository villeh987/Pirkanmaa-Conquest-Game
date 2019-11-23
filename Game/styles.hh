#ifndef STYLES_HH
#define STYLES_HH

#include "mapitem.hh"
#include <QPainter>


namespace Game {

   void getStyle(int tile_x, int tile_y, std::string type, QPainter& painter, QRectF boundingRect);

}


#endif // STYLES_HH
