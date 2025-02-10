#ifndef GRIDCONTAINER_H
#define GRIDCONTAINER_H

#include "../../ThreadPoolManager/threadpoolmanager.h"
#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../../Objects/Constants/constants.h"
#include <QMutex>


class GridContainer : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit GridContainer(MultiCanvasObject* parent = nullptr);
    explicit GridContainer(QRectF parentRect = QRectF(0,0,0,0));
    ~GridContainer();

    GRIDCONTAINER::CELL_PROPERTIES* addGridItem(MultiCanvasObject* gridItem, int row, int col, int horizontalSpan = 1, int verticalSpan = 1);
    GRIDCONTAINER::CELL_PROPERTIES* addGridItem(QGraphicsItem* gridItem, int row, int col, int horizontalSpan = 1, int verticalSpan = 1);

    GRIDCONTAINER::CELL_PROPERTIES* getCellProperties(MultiCanvasObject* object);
    GRIDCONTAINER::CELL_PROPERTIES* getCellProperties(int row, int column);

    float getWidth() const;
    float getHeight() const;

    void updateMaximums();
    void updateLayout();  // Updates the position of the whole layout from the QMap

    float setMaxWidth(int column, float maxWidth);
    float getMaxWidth(int column);
    float setMaxHeight(int row, float maxHeight);
    float getMaxHeight(int row);

    void setMargins(float top, float right, float bottom, float left);
    float setTopMargin(float top);
    float getTopMargin();
    float setRightMargin(float right);
    float getRightMargin();
    float setBottomMargin(float bottom);
    float getBottomMargin();
    float setLeftMargin(float left);
    float getLeftMargin();

    int setHorizontalSpacing(int horizontalSpacing);
    int getHorizontalSpacing();

    int setVerticalSpacing(int verticalSpacing);
    int getVerticalSpacing();

    GRIDCONTAINER::HorizontalAlignment setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment hAlignment);
    GRIDCONTAINER::HorizontalAlignment getHorizontalAlignment();

    GRIDCONTAINER::VerticalAlignment setVerticalAlignment(GRIDCONTAINER::VerticalAlignment vAlignment);
    GRIDCONTAINER::VerticalAlignment getVerticalAlignment();

    bool locationOccupied(int row, int col);

    void addCallbackFunction(std::function<void()> func);

    bool isContainerBusy();

    QRectF boundingRect() const override;


private:
    int lastRow = 0; // Check how big is the grid based on the items highest row
    int lastColumn = 0; // Check how big is the grid based on the items highest column

    QList<float> maxWidth; // Maximum width measured through each colum to set all subsequent rows of the same column with the same width.
    QList<float> maxHeight; // Maximum height measued through each row to set all subsequent columns of the same row with the same height.

    QRectF parentRect = QRectF(0,0,0,0);

    int horizontalSpacing = 0;
    int verticalSpacing = 0;

    float topMargin = 0;
    float bottomMargin = 0;
    float leftMargin = 0;
    float rightMargin = 0;

    GRIDCONTAINER::VerticalAlignment verticalAlignment = GRIDCONTAINER::VerticalAlignment::TOP;
    GRIDCONTAINER::HorizontalAlignment horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;

    QMap<GRIDCONTAINER::CELL_PROPERTIES*,QGraphicsItem*> map; // The location position of each MultiCanvasObject to update the layout.
    QList<std::function<void()>> callbackFunctions;

    QMutex mutex;
    bool containerBusy = false;

public slots:
    void onSetPosition(QGraphicsItem* item, QPointF pos);
    void onTriggerCallbackFunctions();

signals:
    void setPosition(QGraphicsItem* item,QPointF pos);
    void triggerCallbackFunctions();

};

#endif // GRIDCONTAINER_H
