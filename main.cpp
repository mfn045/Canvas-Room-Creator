#include "roomcanvas.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoomCanvas w;
    w.setWindowTitle("Clubpenguin Room Creator");
    w.setWindowIcon(QIcon(":/resources/Resources/logo.png"));
    w.show();
    return a.exec();
}
