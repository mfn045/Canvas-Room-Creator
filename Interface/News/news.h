#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"

class News : public AbstractButton
{
    Q_OBJECT
public:
    explicit News(MultiCanvasObject* parent = nullptr);

    void showNotification();
    void hideNotification();

private:
    MultiCanvasObject* notification = nullptr;
};

#endif // MAP_H
