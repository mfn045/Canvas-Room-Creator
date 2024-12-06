#ifndef CANVASOBJECT_H
#define CANVASOBJECT_H

#include <QGraphicsPixmapItem>
#include <QDir>
#include <QMap>
#include <QCollator>

enum ACTION {
    CLICKABLE = 1,
    HOVERABLE = 2,
    MOUSE_TRACKABLE = 4
};

enum DIRECTION {
    S,
    SW,
    W,
    NW,
    N,
    NE,
    E,
    SE,
};

enum STATE {
    STANDING,
    SITTING,
    WALKING,
    DANCING,
    WAVING
};

struct PROPERTIES {
    DIRECTION currentDirection = DIRECTION::S;
    STATE currentState = STATE::STANDING;
};


class CanvasObject : public QGraphicsPixmapItem
{
public:
    CanvasObject(QString string);
    CanvasObject(CanvasObject* obj);

    void initFrames(QString filePath,DIRECTION direction = DIRECTION::S,STATE state = STATE::STANDING);
    QList<QPixmap>* getCurrentFrames(DIRECTION direction = DIRECTION::S,STATE state = STATE::STANDING);
    QList<QPixmap>* setCurrentFrames(DIRECTION direction = DIRECTION::S,STATE state = STATE::STANDING);
    void nextFrame(bool loop = true, bool force = false);
    void setFrame(int currentFrame);
    void prevFrame(bool loop = true, bool force = false);
    int getCurrentFrame();
    bool isFramePaused();

    QString getFilePath();

    int getID();
    int setID(int id);

    QString getName();
    QString setName(QString name);



private:
    PROPERTIES* objectProperties;
    /**
     * @brief actionFlags is an integer that contains all actions in its bits.
     */
    int actionFlags = 0;
    /**
     * @brief currentFrame is an integer of the current frame.
     */
    int currentFrame = 0;

    /**
     * @brief filePath is the path of the image/sprite file in QString.
     */
    QString filePath;

    /**
     * @brief frames is a list of frame images in QPixmap object.
     */
    QMap<PROPERTIES*,QList<QPixmap>*> frames;

    /**
     * @brief currentFrames is the list of frames
     */
    QList<QPixmap>* currentFrames;

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
     * @brief isVisible is a boolean that will show the frames if its toggled as visible.
     */
    bool isVisible = true;

    /**
     * @brief origin is a QPointF of where the center of mass of the object is.
     */
    QPointF origin;

    STATE defState;
};

#endif // CANVASOBJECT_H
