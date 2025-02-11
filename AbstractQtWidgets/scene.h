#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QObject>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    int getUniqueID();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void mouseMoved(QPointF pos);
    void mousePressed(QPointF pos);
    void keyPressed(int key);
    void keyReleased(int key);

private:
    int id_increment = 0;

};

#endif // SCENE_H
