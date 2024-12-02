#include "roomcanvas.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoomCanvas w;
    w.setWindowTitle("Clubpenguin Room Canvas");
    w.show();
    return a.exec();
}
