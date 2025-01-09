#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"

class News : public AbstractButton
{
    Q_OBJECT
public:
    explicit News(CanvasObject* parent = nullptr);

    void showNotification();
    void hideNotification();

private:
    CanvasObject* notification = nullptr;
};

#endif // MAP_H
