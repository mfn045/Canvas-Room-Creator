#ifndef CANVASOBJECT_H
#define CANVASOBJECT_H

#include <QGraphicsPixmapItem>
#include <QDir>
#include <QCollator>

class CanvasObject : public QGraphicsPixmapItem
{
public:
    CanvasObject(QString string);
    CanvasObject(CanvasObject* obj);
    QList<QPixmap> getFrames();
    void nextFrame();
    void setFrame(int frame);
    void prevFrame();
    int getCurrentFrame();
    QString getFilePath();
    int getID();
    int setID(int id);

private:
    int frame = 0;
    QString filePath;
    QList<QPixmap> frames;
    int id = 0;
};

#endif // CANVASOBJECT_H
