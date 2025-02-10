#ifndef ROOMCANVAS_H
#define ROOMCANVAS_H

#include <QMainWindow>
#include <QGraphicsView>
#include "widgets/openglwidget.h"
#include "widgets/scene.h"
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractButton>
#include <QSizePolicy>
#include <QMenu>
#include "widgets/layers.h"
#include "widgets/canvas.h"
#include "CanvasObject/Multi/multicanvasobject.h"
#include "CanvasObject/Atlas/atlascanvasobject.h"
#include "ThreadPoolManager/threadpoolmanager.h"
#include <QInputDialog>
#include <QMouseEvent>

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
    void remItemByCanvasObject(MultiCanvasObject* canvasObj);
    //QList<CanvasObject*>& getItems();
    QString getFilePath();
    //void setDialogFilePaths(PropertiesDialog& dialog, MultiCanvasObject* obj, STATE state);
    void updateLayers();

    Scene* getScene();
    Canvas* getCanvas();

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

    void mouseTracker(QPoint pos);
    void on_actionRename_Item_triggered();

    void on_actionAdd_child_sprite_to_selected_triggered();

    void on_actionAdd_child_sprite_file_to_selected_triggered();

    void on_actionScale_Selected_triggered();

    void on_actionObject_Properties_triggered();

    void on_actionSet_origin_triggered();

private:
    Ui::RoomCanvas *ui;

    Scene* scene;
    Canvas* canvas;
    Layers* layers;

    bool attemptingUpdate = false;
    bool updatingSelection = false;

    QList<Qt::Key> pressedKeys;

    int id_increment = 0;

    QGraphicsItem* selectingOrigin = nullptr;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void keyPressed(int key);
};
#endif // ROOMCANVAS_H
