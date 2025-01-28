#ifndef CLOTHES_H
#define CLOTHES_H

class Clothes {
public:
    enum TYPE {
        COLOR=1,
        HEAD,
        FACE,
        NECK,
        BODY,
        HAND,
        FEET,
        PIN,
        BACKGROUND,
        AWARD
    };

    Clothes();

    int getHeadItem();
    int setHeadItem(int headItem_ID);

    int getFaceItem();
    int setFaceItem(int faceItem_ID);

    int getNeckItem();
    int setNeckItem(int neckItem_ID);

    int getBodyItem();
    int setBodyItem(int bodyItem_ID);

    int getFeetItem();
    int setFeetItem(int feetItem_ID);

    int getPinItem();
    int setPinItem(int pinItem_ID);

    int getBackgroundItem();
    int setBackgroundItem(int backgroundItem_ID);

private:
    short headItem_ID = 0;
    short faceItem_ID = 0;
    short neckItem_ID = 0;
    short bodyItem_ID = 0;
    short handItem_ID = 0;
    short feetItem_ID = 0;
    short pinItem_ID = 0;
    short backgroundItem_ID = 0;
};
#endif // CLOTHES_H
