#ifndef MODERATOR_H
#define MODERATOR_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"

class Moderator : public AbstractButton
{
    Q_OBJECT
public:
    explicit Moderator(CanvasObject* parent = nullptr);
};

#endif // MAP_H
