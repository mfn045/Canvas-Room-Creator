#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QApplication>
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Widgets/Buttons/BlueButton/bluebutton.h"
#include "Interface/Widgets/Buttons/OrangeButton/orangebutton.h"
#include "AbstractQtWidgets/scene.h"
#include "Interface/Common/TextLabel/textlabel.h"

class AbstractDialog : public MultiCanvasObject
{
    Q_OBJECT
public:
    enum class TYPE {
        ORANGE,
        BLUE
    };

    enum class BUTTONS_LAYOUT {
        HORIZONTAL,
        VERTICAL
    };

    explicit AbstractDialog(Scene* parent = nullptr, TYPE type = TYPE::BLUE);

    TYPE setType(TYPE type);
    TYPE getType();

    int getRow();
    int setRow(int row);

    int getCol();
    int setCol(int col);

    float getGridSize();
    float setGridSize(float size);

    void setElementsPositions(float& elementsHeight, float& buttonsWidth) const;
    QList<float> approximateMeasurements() const;

    BUTTONS_LAYOUT getButtonsLayout() const;
    BUTTONS_LAYOUT setButtonsLayout(BUTTONS_LAYOUT buttonsLayout);

    void setDialogPosition();

    TextLabel* insertText(QString text);

    AbstractButton* addButton(QString buttonName);

    Scene* getScene();

protected:
    bool init();

    QList<AbstractButton*> buttons;

    QList<TextLabel*> textLabels;

    QRectF boundingRect() const override {
        QRectF rect;
        for (const QGraphicsItem *child : childItems()) {
            rect = rect.united(child->mapToParent(child->boundingRect()).boundingRect());
        }
        return rect;
    }

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

    BUTTONS_LAYOUT buttonsLayout = BUTTONS_LAYOUT::HORIZONTAL;

    Scene* scene = nullptr;

    int row = 0;
    int col = 0;

    float outter_paddingX = 40;
    float element_spacingY = 10;
    float button_spacingXY = 10;

    float gridSize = 0;
};

#endif // DIALOG_H
