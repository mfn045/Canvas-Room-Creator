#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDomDocument>

namespace PENGUIN {
enum DIRECTION {
    S,
    SW,
    W,
    NW,
    N,
    NE,
    E,
    SE,
};

enum STATE {
    STANDING,
    SITTING,
    WALKING,
    DANCING,
    WAVING
};

enum BADGE {
    NONE,
    PLAYER,
    MEMBER_0,
    MEMBER_1,
    MEMBER_2,
    MEMBER_3,
    MEMBER_4
};
};
namespace CLOTHES {
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
}
namespace CANVAS {
enum ACTION {
    CLICKABLE = 1,
    HOVERABLE = 2,
    MOUSE_TRACKABLE = 4
};
struct Frame {
    int xmin = 0;
    int xmax = 0;
    int ymin = 0;
    int ymax = 0;
    QDomDocument r;
};
}

#endif // CONSTANTS_H
