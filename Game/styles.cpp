#include "styles.hh"

namespace Game {


void getStyle(int tile_x, int tile_y, std::string type, QPainter& painter, QRectF boundingRect, QColor player_color)
{

    if (type == "Teekkari"){


        QPointF overall[21] = {
            QPointF(tile_x+30, tile_y-15),
            QPointF(tile_x+30, tile_y),
            QPointF(tile_x+22.5, tile_y),
            QPointF(tile_x+22.5, tile_y-20),
            QPointF(tile_x+25, tile_y-20),
            QPointF(tile_x+25, tile_y-25),
            QPointF(tile_x+25, tile_y-20),
            QPointF(tile_x+20, tile_y-20),
            QPointF(tile_x+20, tile_y-25),
            QPointF(tile_x+20, tile_y-30),
            QPointF(tile_x+22.5, tile_y-35),
            QPointF(tile_x+37.5, tile_y-35),
            QPointF(tile_x+40, tile_y-30),
            QPointF(tile_x+40, tile_y-20),
            QPointF(tile_x+35, tile_y-20),
            QPointF(tile_x+35, tile_y-25),
            QPointF(tile_x+35, tile_y-20),
            QPointF(tile_x+37.5, tile_y-20),
            QPointF(tile_x+37.5, tile_y),
            QPointF(tile_x+30, tile_y),
            QPointF(tile_x+30, tile_y-15)
        };

        QPointF teekkari_face[8] = {
            QPointF(tile_x+26.5, tile_y-42.5),
            QPointF(tile_x+26.5, tile_y-37.5),
            QPointF(tile_x+27.5, tile_y-35),
            QPointF(tile_x+32.5, tile_y-35),
            QPointF(tile_x+33.5, tile_y-37.5),
            QPointF(tile_x+33.5, tile_y-42.5),
            QPointF(tile_x+30, tile_y-41),
            QPointF(tile_x+26.5, tile_y-42.5)
        };

        QPointF teekkari_cap_black_part[7] = {
            QPointF(tile_x+25, tile_y-42.5),
            QPointF(tile_x+25, tile_y-43.5),
            QPointF(tile_x+30, tile_y-42.5),
            QPointF(tile_x+35, tile_y-43.5),
            QPointF(tile_x+35, tile_y-42.5),
            QPointF(tile_x+30, tile_y-41),
            QPointF(tile_x+25, tile_y-42.5),
        };

        QPointF teekkari_cap_white_part[7] = {
            QPointF(tile_x+25, tile_y-43.5),
            QPointF(tile_x+25, tile_y-45),
            QPointF(tile_x+30, tile_y-47),
            QPointF(tile_x+35, tile_y-45),
            QPointF(tile_x+35, tile_y-43.5),
            QPointF(tile_x+30, tile_y-42.5),
            QPointF(tile_x+25, tile_y-43.5),
        };

        QPointF teekkari_cap_string[5] = {
            QPointF(tile_x+30, tile_y-45),
            QPointF(tile_x+25, tile_y-45),
            QPointF(tile_x+25, tile_y-35),
            QPointF(tile_x+25, tile_y-45),
            QPointF(tile_x+30, tile_y-45)
        };

        QPointF teekkari_cap_tassel[4] = {
            QPointF(tile_x+25, tile_y-35),
            QPointF(tile_x+23, tile_y-30),
            QPointF(tile_x+27, tile_y-30),
            QPointF(tile_x+25, tile_y-35)
        };

        QPointF right_eye[5] = {
            QPointF(tile_x+27, tile_y-40),
            QPointF(tile_x+28, tile_y-40),
            QPointF(tile_x+28, tile_y-41),
            QPointF(tile_x+27, tile_y-41),
            QPointF(tile_x+27, tile_y-40)
        };

        QPointF left_eye[5] = {
            QPointF(tile_x+32, tile_y-40),
            QPointF(tile_x+33, tile_y-40),
            QPointF(tile_x+33, tile_y-41),
            QPointF(tile_x+32, tile_y-41),
            QPointF(tile_x+32, tile_y-40)
        };

        QPointF teekkari_mouth[3] = {
            QPointF(tile_x+27.5, tile_y-37),
            QPointF(tile_x+31.5, tile_y-37),
            QPointF(tile_x+27.5, tile_y-37)
        };



        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QColor(128, 128, 128));
        painter.drawPolygon(overall, 21);

        painter.setBrush(QColor(Qt::red));
        painter.drawEllipse(QPointF(QPointF(tile_x+27, tile_y-2.5)), 2, 2);

        painter.setBrush(QColor(Qt::green));
        painter.drawEllipse(QPointF(QPointF(tile_x+35.5, tile_y-10)), 2, 3);

        painter.setBrush(QColor(Qt::blue));
        painter.drawEllipse(QPointF(QPointF(tile_x+25, tile_y-13)), 3, 2);

        painter.setBrush(QColor(204, 204, 0));
        painter.drawEllipse(QPointF(QPointF(tile_x+37.5, tile_y-27)), 2, 2);

        painter.setBrush(QColor(Qt::white));
        painter.drawEllipse(QPointF(QPointF(tile_x+33, tile_y-22)), 2, 2);

        painter.setBrush(QColor(255, 0, 127));
        painter.drawEllipse(QPointF(QPointF(tile_x+31, tile_y-21)), 2, 2);

        painter.setBrush(QColor(Qt::black));
        painter.drawEllipse(QPointF(QPointF(tile_x+28, tile_y-20)), 2, 2);

        painter.setBrush(QColor(255, 178, 102));
        painter.drawPolygon(teekkari_face, 8);
        //painter.setBrush(QColor(Qt::black));
        painter.setPen(QPen(QColor(Qt::black), 0.5));
        painter.drawPolygon(right_eye, 5);
        painter.drawPolygon(left_eye, 5);
        painter.drawPolygon(teekkari_mouth, 3);
        painter.setPen(QPen(QColor(Qt::black), 1));
        painter.drawPolygon(teekkari_cap_black_part, 7);
        painter.setBrush(QColor(Qt::white));
        painter.drawPolygon(teekkari_cap_white_part, 7);
        painter.setPen(QPen(Qt::black, 0.5));
        painter.drawPolygon(teekkari_cap_string, 5);
        painter.setPen(QPen(Qt::black, 1));
        painter.setBrush(QColor(Qt::black));
        painter.drawPolygon(teekkari_cap_tassel, 4);

    }

    if (type == "Lava") {
        painter.setBrush(QBrush(QColor(255, 137, 0)));
        painter.drawRect(boundingRect);
    }

    if (type == "Rock") {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(QColor(64, 64, 64)));
        painter.drawRect(boundingRect);

        QPointF small_mountain[10] = {
            QPointF(tile_x+5, tile_y-35),
            QPointF(tile_x+7, tile_y-40),
            QPointF(tile_x+8, tile_y-38),
            QPointF(tile_x+10, tile_y-45),
            QPointF(tile_x+13, tile_y-43),
            QPointF(tile_x+15, tile_y-49),
            QPointF(tile_x+17.5, tile_y-38),
            QPointF(tile_x+18, tile_y-40),
            QPointF(tile_x+20, tile_y-35),
            QPointF(tile_x+5, tile_y-35)
        };

        QPointF large_mountain[11] = {
            QPointF(tile_x+15, tile_y-5),
            QPointF(tile_x+20, tile_y-15),
            QPointF(tile_x+22.5, tile_y-12.5),
            QPointF(tile_x+25, tile_y-20),
            QPointF(tile_x+27.5, tile_y-17.5),
            QPointF(tile_x+35, tile_y-30),
            QPointF(tile_x+40, tile_y-20),
            QPointF(tile_x+42, tile_y-25),
            QPointF(tile_x+45, tile_y-15),
            QPointF(tile_x+50, tile_y-5),
            QPointF(tile_x+15, tile_y-5)
        };

        QPointF snow_top[11] = {
            QPointF(tile_x+27.5, tile_y-17.5),
            QPointF(tile_x+30, tile_y-17),
            QPointF(tile_x+32.5, tile_y-18),
            QPointF(tile_x+35, tile_y-16),
            QPointF(tile_x+38, tile_y-18),
            QPointF(tile_x+42, tile_y-16),
            QPointF(tile_x+44, tile_y-18),
            QPointF(tile_x+42, tile_y-25),
            QPointF(tile_x+40, tile_y-20),
            QPointF(tile_x+35, tile_y-30),
            QPointF(tile_x+27.5, tile_y-17.5)
        };

        QPen mountain_pen = QPen(QColor(Qt::black), 1);

        painter.setPen(mountain_pen);
        painter.drawPolygon(small_mountain, 10);
        painter.drawPolygon(large_mountain, 11);
        painter.setBrush(QColor(Qt::white));
        painter.drawPolygon(snow_top, 11);

    }

    if (type == "Water") {

        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(QColor(Qt::blue)));
        painter.drawRect(boundingRect);
    }

    if (type == "Forest") {

        painter.setPen(QPen(Qt::black));
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

        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

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

        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

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

        QRectF source2(-200, -400, 800, 800);
        QPixmap pixmap2("cigarette.png");
        painter.drawPixmap(boundingRect, pixmap2, source2);
    }

    if (type == "HeadQuarters") {

        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("headquarters.png");
        painter.drawPixmap(boundingRect, pixmap, source);
    }
    if (type == "Farm") {


        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("farm.png");
        painter.drawPixmap(boundingRect, pixmap, source);

    }



    if (type == "Outpost") {

        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

        QRectF source(-100, 0, 700, 700);
        QPixmap pixmap("outpost.png");
        painter.drawPixmap(boundingRect, pixmap, source);

    }

    if (type == "Mine") {

        setBoundingRectColor(tile_x, tile_y, player_color, painter, boundingRect);

        QRectF source(-100, 0, 500, 500);
        QPixmap pixmap("mine.png");
        painter.drawPixmap(boundingRect, pixmap, source);
    }



    if (type == "Grassland") {

        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(QColor(108, 255, 0)));
        painter.drawRect(boundingRect);
    }




}

void setBoundingRectColor(int tile_x, int tile_y, QColor player_color, QPainter& painter, QRectF boundingRect)
{
    QPen color_bound(player_color, 2);

    painter.setPen(color_bound);

    QRectF color_bound_rect(tile_x, tile_y-50, boundingRect.width(), boundingRect.height());

    painter.drawRect(color_bound_rect);
}

}

