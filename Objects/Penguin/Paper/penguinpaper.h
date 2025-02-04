#ifndef PENGUINPAPER_H
#define PENGUINPAPER_H

#include <QDomDocument>
#include <QJsonDocument>
#include "../../../CanvasObject/Multi/multicanvasobject.h"

class PenguinPaper : public MultiCanvasObject
{
public:
    explicit PenguinPaper(MultiCanvasObject* parent = nullptr);

    void changeColor(QString color);

    void setHead(int headId);
    void setFace(int faceId);
    void setNeck(int neckId);
    void setBody(int bodyId);
    void setHand(int handId);
    void setFeet(int feetId);
    void setPin(int pinId);
    void setBackground(int backgroundId);
    void setColor(int colorId);

private:
    MultiCanvasObject* loadItem(int id);
    MultiCanvasObject* head = nullptr;
    MultiCanvasObject* face = nullptr;
    MultiCanvasObject* neck = nullptr;
    MultiCanvasObject* body = nullptr;
    MultiCanvasObject* hand = nullptr;
    MultiCanvasObject* feet = nullptr;
    MultiCanvasObject* pin = nullptr;
    MultiCanvasObject* background = nullptr;

};

#endif // PENGUINPAPER_H
