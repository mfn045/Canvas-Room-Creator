#ifndef CONSTANTS_H
#define CONSTANTS_H

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

#endif // CONSTANTS_H
