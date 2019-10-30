#include "mapwindow.hh"

#include <QApplication>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    MapWindow mapWindow;
    mapWindow.show();
    mapWindow.showStartDialog();
    return app.exec();
}
