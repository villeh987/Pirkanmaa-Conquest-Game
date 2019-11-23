#include "styles.hh"

namespace Game {


void getStyle(int tile_x, int tile_y, std::string type, QPainter& painter, QRectF boundingRect)
{

    if (type == "Forest") {



        QPointF tree_trunk[5] = {
            QPointF(tile_x+4.2,tile_y-37),
            QPointF(tile_x+4.2,tile_y-40),
            QPointF(tile_x+5.8,tile_y-40),
            QPointF(tile_x+5.8,tile_y-37),
            QPointF(tile_x+4.2,tile_y-37)

        };


        QPointF tree_leaves_left[8] = {
            QPointF(tile_x+5, tile_y-41),
            QPointF(tile_x+1, tile_y-40),
            QPointF(tile_x+5, tile_y-44),
            QPointF(tile_x+1.5, tile_y-43),
            QPointF(tile_x+5, tile_y-47),
            QPointF(tile_x+3, tile_y-47),
            QPointF(tile_x+5, tile_y-49),
            QPointF(tile_x+5, tile_y-41)
        };


        QPointF tree_leaves_right[8] = {
            QPointF(tile_x+5, tile_y-41),
            QPointF(tile_x+9, tile_y-40),
            QPointF(tile_x+5, tile_y-44),
            QPointF(tile_x+8.5, tile_y-43),
            QPointF(tile_x+5, tile_y-47),
            QPointF(tile_x+7, tile_y-47),
            QPointF(tile_x+5, tile_y-49),
            QPointF(tile_x+5, tile_y-41)

        };


        QBrush tree_trunk_brush = QColor(102, 50, 0);
        QBrush tree_leaves_brush = QColor(128, 255, 0);

        QPen tree_trunk_pen = QPen(QColor(102, 50, 0));
        QPen tree_leaves_pen = QPen(QColor(128, 255, 0));

        painter.setBrush(QBrush(QColor(0, 102, 0)));
        painter.drawRect(boundingRect);

        painter.setBrush(tree_leaves_brush);
        painter.setPen(tree_leaves_pen);

        painter.drawPolygon(tree_leaves_left, 8);
        painter.drawPolygon(tree_leaves_right, 8);

        painter.setBrush(tree_trunk_brush);
        painter.setPen(tree_trunk_pen);


        painter.drawPolygon(tree_trunk, 5);

    }

    if (type == "TuniTower") {
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

        painter.setBrush(QBrush(QColor(204, 102, 0)));

        painter.setPen(tuni_pen);

        painter.drawPolygon(tuni_tower, 4);
        painter.setBrush(tuni_face_brush);
        painter.drawPolygon(tuni_forehead, 9);
        painter.drawPolygon(tuni_right_eye, 5);
        painter.drawPolygon(tuni_left_eye, 7);
        painter.drawPolygon(tuni_cheeck, 12);

    }

    if (type == "BasicWorker") {
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

        painter.setPen(tuni_pen);

        painter.setBrush(tuni_face_brush);

        painter.drawPolygon(tuni_forehead, 9);
        painter.drawPolygon(tuni_right_eye, 5);
        painter.drawPolygon(tuni_left_eye, 7);
        painter.drawPolygon(tuni_cheeck, 12);


        QRectF source(-300, 10, 1100, 1100);
        QPixmap pixmap("workerhelmet.png");
        painter.drawPixmap(boundingRect, pixmap, source);

        //QRectF target2 = boundingRect();
        QRectF source2(-200, -400, 800, 800);
        QPixmap pixmap2("cigarette.png");
        painter.drawPixmap(boundingRect, pixmap2, source2);
    }

    if (type == "HeadQuarters") {

        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("headquarters.png");
        painter.drawPixmap(boundingRect, pixmap, source);
    }
    if (type == "Farm") {
        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("farm.png");
        painter.drawPixmap(boundingRect, pixmap, source);

    }

    if (type == "Outpost") {
        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("outpost.png");
        painter.drawPixmap(boundingRect, pixmap, source);

    }

    if (type == "Mine") {
        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("mine.png");
        painter.drawPixmap(boundingRect, pixmap, source);
    }

    if (type == "Water") {
        painter.setBrush(QBrush(QColor(Qt::blue)));
        painter.drawRect(boundingRect);
    }

    if (type == "Grassland") {
        painter.setBrush(QBrush(QColor(108, 255, 0)));
        painter.drawRect(boundingRect);
    }

}



}
