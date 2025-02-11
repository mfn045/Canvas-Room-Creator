#include "moderator.h"

Moderator::Moderator(MultiCanvasObject* parent) : AbstractButton(parent) {
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/moderator_over";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/moderator_down";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
}
