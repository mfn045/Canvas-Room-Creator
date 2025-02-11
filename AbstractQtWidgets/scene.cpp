#include "scene.h"

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    QRectF f;
    f.setRect(0,0,800,600);
    setSceneRect(f);
}

int Scene::getUniqueID(){
    id_increment++;
    return id_increment;
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit mouseMoved(event->scenePos());
    return QGraphicsScene::mouseMoveEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event){
    emit keyPressed(event->key());
    return QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event){
    emit keyReleased(event->key());
    return QGraphicsScene::keyReleaseEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit mousePressed(event->scenePos());
    return QGraphicsScene::mousePressEvent(event);
}
