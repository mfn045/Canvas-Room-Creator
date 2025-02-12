#include "moderator.h"

Moderator::Moderator(MultiCanvasObject* parent) : AbstractButton(parent) {
    QString upButton = "D:/Workspace/Clubpenguin-Room-Creator/assets/interface/world/buttons/moderator/up.svg";
    QString overButton = "D:/Workspace/Clubpenguin-Room-Creator/assets/interface/world/buttons/moderator/over.svg";
    QString downButton = "D:/Workspace/Clubpenguin-Room-Creator/assets/interface/world/buttons/moderator/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
}
