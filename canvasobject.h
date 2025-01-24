#ifndef CANVASOBJECT_H
#define CANVASOBJECT_H

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QDomDocument>
#include <QDomElement>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDir>
#include <QCursor>
#include <QMap>
#include <QCollator>
#include <QGraphicsSceneDragDropEvent>


class CanvasObject : public QGraphicsSvgItem
{
    Q_OBJECT
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

    explicit CanvasObject(CanvasObject* parent = nullptr);
    explicit CanvasObject(QString filePath, CanvasObject* parent = nullptr);

    ~CanvasObject();

    void initFrames(QString filePath,PROPERTIES* properties);
    QList<QByteArray*>& getCurrentFrames();
    QMap<PROPERTIES*, QList<QByteArray*>>& getFrames();
    QList<QByteArray*>& setCurrentFrames(PROPERTIES* properties);
    PROPERTIES* getCurrentProperties();
    void nextFrame(bool loop = true, bool force = false);
    void setFrame(int currentFrame);
    void prevFrame(bool loop = true, bool force = false);
    int getCurrentFrame();
    bool isFramePaused();

    int getID();
    int setID(int id);

    QString getName();
    QString setName(QString name);

    bool containsActionFlag(ACTION flag);
    void setActionFlags(int flags);
    int getActionFlags();

    QPointF getOrigin();
    QPointF setOrigin(QPointF origin);

    CONST_POSITION setConstPosition(CONST_POSITION newConst);
    CONST_POSITION getConstPosition();

    bool isMouseTrackable();
    bool setIsMouseTrackable(bool trackable);
    bool isClickable();
    bool setIsClickable(bool isClickable);
    bool isHoverable();
    bool setIsHoverable(bool isClickable);

    bool hasAnimationLoop();
    bool setHasAnimationLoop(bool animationLoop);
    bool isAnimationOn();
    bool setIsAnimationOn(bool animationOn);

    bool isTransparentPixel(QPointF pos);

    void refresh();

    //double setScale(double scale);
    //double getScale();

    int child_id_increment = 0;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    /**
     * @brief actionFlags is an integer that contains all actions in its bits.
     */
    unsigned short actionFlags = 0;
    /**
     * @brief currentFrame is an integer of the current frame.
     */
    int currentFrame = 0;

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
     * @brief id is the ID of the canvas object.
     */
    int id = 0;

    /**
     * @brief name is a QString for the CanvasObject's layer name.
     */
    QString name = "";

    /**
     * @brief framePauses is a list of frames where it will pause animation.
     */
    QList<int> framePauses;

    /**
     * @brief origin is a QPointF of where the center of mass of the object is.
     */
    QPointF origin;

    double scale = 1;

    bool isSettingFrame = false;

    bool animationLoop = false;

    bool animationOn = true;

    bool isImageLatest = false;

    std::unique_ptr<QImage> image;

    CONST_POSITION posConst = CONST_POSITION::TOP;

signals:
    virtual void animationDone();
    void hoverEnter(QPointF pos);
    void hoverLeave(QPointF pos);
    void hoverMove(QPointF pos);
    void mousePress(QPointF pos);
    void mouseMove(QPointF pos);
    void mouseRelease(QPointF pos);
};

#endif // CANVASOBJECT_H
