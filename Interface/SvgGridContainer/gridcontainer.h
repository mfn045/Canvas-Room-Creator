#ifndef GRIDCONTAINER_H
#define GRIDCONTAINER_H

#include "../../canvasobject.h"

class GridContainer : public CanvasObject
{
public:
    enum class VerticalAlignment {
        TOP,
        CENTER,
        BOTTOM,
    };
    enum class HorizontalAlignment {
        LEFT,
        CENTER,
        RIGHT,
    };
    struct CELL_PROPERTIES {
        int row = 0;
        int col = 0;

        int verticalSpan = 1;
        int horizontalSpan = 1;

        VerticalAlignment verticalAlignment = VerticalAlignment::CENTER;
        HorizontalAlignment horizontalAlignment = HorizontalAlignment::CENTER;

        bool operator==(CELL_PROPERTIES& properties){
            if(properties.col == col && properties.row == row){
                return true;
            }
            return false;
        }
    };
    explicit GridContainer(CanvasObject* parent = nullptr);
    explicit GridContainer(QRectF parentRect = QRectF(0,0,0,0));

    CanvasObject* addGridItem(CanvasObject* gridItem, int row, int col, int horizontalSpan = 1, int verticalSpan = 1);

    int setHorizontalSpacing(int horizontalSpacing);
    int getHorizontalSpacing();

    int setVerticalSpacing(int verticalSpacing);
    int getVerticalSpacing();

    void setMargins(float top, float right, float bottom, float left);
    float setTopMargin(float top);
    float getTopMargin();
    float setRightMargin(float right);
    float getRightMargin();
    float setBottomMargin(float bottom);
    float getBottomMargin();
    float setLeftMargin(float left);
    float getLeftMargin();

    float getWidth();
    float getHeight();

    void updateMaximums();

    bool locationOccupied(int row, int col);

    void updateLayout(); // Updates the position of the whole layout from the QMap

private:
    int lastRow = 0; // Check how big is the grid based on the items highest row
    int lastColumn = 0; // Check how big is the grid based on the items highest column

    QList<float> maxWidth; // Maximum width measured through each colum to set all subsequent rows of the same column with the same width.
    QList<float> maxHeight; // Maximum height measued through each row to set all subsequent columns of the same row with the same height.

    QRectF parentRect;

    int horizontalSpacing = 0;
    int verticalSpacing = 0;

    float topMargin = 0;
    float bottomMargin = 0;
    float leftMargin = 0;
    float rightMargin = 0;

    VerticalAlignment verticalAlignment = VerticalAlignment::TOP;
    HorizontalAlignment horizontalAlignment = HorizontalAlignment::LEFT;

    QMap<CELL_PROPERTIES*,CanvasObject*> map; // The location position of each canvasobject to update the layout.
};

#endif // GRIDCONTAINER_H
