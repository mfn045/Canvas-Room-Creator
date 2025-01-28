#ifndef PENGUINPAPER_H
#define PENGUINPAPER_H

#include "../../../canvasobject.h"

class PenguinPaper : public CanvasObject
{
public:
    explicit PenguinPaper(CanvasObject* parent = nullptr);

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
    CanvasObject* loadItem(int id);
    CanvasObject* head = nullptr;
    CanvasObject* face = nullptr;
    CanvasObject* neck = nullptr;
    CanvasObject* body = nullptr;
    CanvasObject* hand = nullptr;
    CanvasObject* feet = nullptr;
    CanvasObject* pin = nullptr;
    CanvasObject* background = nullptr;

};

#endif // PENGUINPAPER_H
