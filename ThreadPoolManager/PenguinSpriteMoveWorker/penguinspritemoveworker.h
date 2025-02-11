#ifndef PENGUINSPRITEMOVEWORKER_H
#define PENGUINSPRITEMOVEWORKER_H

#include <QThread>
#include <QRunnable>
#include "Interface/Common/CanvasObject/abstractcanvasobject.h"

class PenguinSpriteMoveWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    PenguinSpriteMoveWorker();

    bool hasStarted();

    void run() override;
private:
    QHash<AbstractCanvasObject*,QPointF> movingSprites; // Sprite -> Destination
    bool started = false;

public slots:
    void addToMovingSprites(AbstractCanvasObject* sprite, QPointF destination);

signals:
    void finished();
};

#endif // PENGUINSPRITEMOVEWORKER_H
