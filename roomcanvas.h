#ifndef ROOMCANVAS_H
#define ROOMCANVAS_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QSizePolicy>
#include <QMenu>
#include "layers.h"
#include "canvasobject.h"
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class RoomCanvas;
}
QT_END_NAMESPACE

class RoomCanvas : public QMainWindow
{
    Q_OBJECT

public:
    RoomCanvas(QWidget *parent = nullptr);
    ~RoomCanvas();
    Q_INVOKABLE void nextFrame();
    void addItem(QString dir);
    void remItem(QString dir);
    void remItemByID(int id);
    QList<CanvasObject*> getItems();
    void updateLayers();

private slots:
    void on_importSpriteFile_triggered();
    void on_actionImport_Sprite_triggered();
    void updateItems();
    void on_actionMove_Selected_triggered();
    void changeGraphicsSelection();
    void changeLayersSelection();
    void on_editDimensionsAction_triggered();
    void on_actionRemove_Selected_triggered();
    void contextMenuRequested(QPoint point);

private:
    Ui::RoomCanvas *ui;
    QThread* thread;
    QList<CanvasObject*> items;
    QGraphicsScene* scene;
    Layers* layers;
    bool attemptingUpdate = false;
    bool updatingSelection = false;
};
#endif // ROOMCANVAS_H
