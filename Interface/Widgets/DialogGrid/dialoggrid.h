#ifndef DIALOGGRID_H
#define DIALOGGRID_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "AbstractQtWidgets/scene.h"

class DialogGrid : public MultiCanvasObject
{
public:
    enum class TYPE {
        ORANGE,
        BLUE
    };

    explicit DialogGrid(Scene* scene = nullptr, TYPE type = TYPE::BLUE);

    TYPE setType(TYPE type);
    TYPE getType();

    int getRow();
    int setRow(int row);

    int getCol();
    int setCol(int col);

    float getGridSizeX();
    float getGridSizeY();
    void setGridSize(float gridSize_X, float gridSize_Y);

    float getWidth() const;
    float setWidth(float width);
    float getHeight() const;
    float setHeight(float height);

    float getScale();
    float setScale(float scale);

    void setDialogPosition();

    Scene* getScene();

    bool init();

    QRectF boundingRect() const override;

private:
    MultiCanvasObject* top = nullptr;
    MultiCanvasObject* top_left = nullptr;
    MultiCanvasObject* top_right = nullptr;
    MultiCanvasObject* left = nullptr;
    MultiCanvasObject* right = nullptr;
    MultiCanvasObject* bottom_left = nullptr;
    MultiCanvasObject* bottom = nullptr;
    MultiCanvasObject* bottom_right = nullptr;
    MultiCanvasObject* center = nullptr;

    QString path_top = "";
    QString path_top_left = "";
    QString path_top_right = "";

    QString path_bottom = "";
    QString path_bottom_left = "";
    QString path_bottom_right = "";

    QString path_center = "";
    QString path_left = "";
    QString path_right = "";

    TYPE type = TYPE::BLUE;

    Scene* scene = nullptr;

    int row = 0;
    int col = 0;

    float gridSize_X = 0;
    float gridSize_Y = 0;

    QTransform gridTransform;
};

#endif // DIALOGGRID_H
