#ifndef DIALOGGRID_H
#define DIALOGGRID_H

#include "../../canvasobject.h"
#include "../../widgets/scene.h"

class DialogGrid : public CanvasObject
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

    float getGridSize();
    float setGridSize(float size);

    float getWidth();
    float getHeight();

    float getScale();
    float setScale(float scale);

    void setDialogPosition();

    Scene* getScene();

    bool init();

private:
    CanvasObject* top = nullptr;
    CanvasObject* top_left = nullptr;
    CanvasObject* top_right = nullptr;
    CanvasObject* left = nullptr;
    CanvasObject* right = nullptr;
    CanvasObject* bottom_left = nullptr;
    CanvasObject* bottom = nullptr;
    CanvasObject* bottom_right = nullptr;
    CanvasObject* center = nullptr;

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

    float gridSize = 0;

    float scale = 1;
};

#endif // DIALOGGRID_H
