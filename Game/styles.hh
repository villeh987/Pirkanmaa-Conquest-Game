#ifndef STYLES_HH
#define STYLES_HH

#include "mapitem.hh"
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>



namespace Game {

   void getStyle(int tile_x, int tile_y, std::string type, QPainter& painter, QRectF boundingRect, QColor player_color, std::vector<std::shared_ptr<Course::WorkerBase> > workers, std::vector<std::shared_ptr<Course::BuildingBase>> buildings);
   void setBoundingRectColor(int tile_x, int tile_y, QColor player_color, QPainter& painter, QRectF boundingRect);
   void drawTree(int tile_x, int tile_y, QPainter& painter);
   void drawTeekkari(int tile_x, int tile_y, QPainter& painter);
   void drawTuniTower(int tile_x, int tile_y, QPainter& painter);
   void drawBasicWorker(int tile_x, int tile_y, QPainter& painter, QRectF boundingRect, int moving_factor_x, int moving_factor_y);
   void drawMiner(int tile_x, int tile_y, QPainter& painter);
   void drawRock(int tile_x, int tile_y, QPainter& painter, QRectF boundingRect);
}


#endif // STYLES_HH
