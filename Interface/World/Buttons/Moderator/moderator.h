#ifndef MODERATOR_H
#define MODERATOR_H

#include <QObject>
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class Moderator : public AbstractButton
{
    Q_OBJECT
public:
    explicit Moderator(MultiCanvasObject* parent = nullptr);
};

#endif // MAP_H
