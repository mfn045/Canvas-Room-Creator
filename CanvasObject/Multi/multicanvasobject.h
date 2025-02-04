#ifndef MULTICANVASOBJECT_H
#define MULTICANVASOBJECT_H

#include <QFile>
#include <QDir>
#include <QCollator>
#include <QStyleOptionGraphicsItem>
#include "../abstractcanvasobject.h"


class MultiCanvasObject : public AbstractCanvasObject
{
public:
    enum ACTION {
        CLICKABLE = 1,
        HOVERABLE = 2,
        MOUSE_TRACKABLE = 4
    };
    struct PROPERTIES {
        QString filePath = "";
        int yOffset = 0;
        int xOffset = 0;
    };

    enum CONST_POSITION {
        TOP,
        BOTTOM
    };

    explicit MultiCanvasObject(MultiCanvasObject* parent = nullptr);

    ~MultiCanvasObject();

    void initFrames(QString filePath,PROPERTIES* properties);
    QList<QByteArray*>& getCurrentFrames();
    QMap<PROPERTIES*, QList<QByteArray*>>& getFrames();
    QList<QByteArray*>& setCurrentFrames(PROPERTIES* properties);
    PROPERTIES* getCurrentProperties();

    void nextFrame(bool loop = true, bool force = false) override;
    void setFrame(int currentFrame) override;
    void prevFrame(bool loop = true, bool force = false) override;

    QPointF getOrigin();
    QPointF setOrigin(QPointF origin);

    CONST_POSITION setConstPosition(CONST_POSITION newConst);
    CONST_POSITION getConstPosition();

    //double setScale(double scale);
    //double getScale();

    void refresh();

    int child_id_increment = 0;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    /**
     * @brief frames is a list of frame images in QPixmap object.
     */
    QMap<PROPERTIES*,QList<QByteArray*>> frames;

    /**
     * @brief currentFrames is the list of frames
     */
    QList<QByteArray*> currentFrames;

    /**
     * @brief currentProperties is the current properties of the frame being displayed
     */
    PROPERTIES* currentProperties;

    /**
     * @brief origin is a QPointF of where the center of mass of the object is.
     */
    QPointF origin;

    bool isSettingFrame = false;

    CONST_POSITION posConst = CONST_POSITION::TOP;

};


#endif // MULTICANVASOBJECT_H
