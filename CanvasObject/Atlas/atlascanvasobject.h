#ifndef ATLASCANVASOBJECT_H
#define ATLASCANVASOBJECT_H

#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStyleOptionGraphicsItem>
#include "../abstractcanvasobject.h"
#include "../../Objects/Constants/constants.h"


class AtlasCanvasObject : public AbstractCanvasObject
{
    Q_OBJECT
public:
    explicit AtlasCanvasObject(AtlasCanvasObject* parent = nullptr);
    explicit AtlasCanvasObject(QString filePath, AtlasCanvasObject* parent = nullptr);

    void initFrames(QString filePath);

    QList<int>& getCurrentSpriteFrames();

    QMap<int, QList<int>>& getSprites();
    QList<int>& setCurrentSprite(int sprite);
    int getCurrentSprite();

    void nextFrame(bool loop = true, bool force = false) override;
    void setFrame(int currentFrame) override;
    void prevFrame(bool loop = true, bool force = false) override;

    //CONST_POSITION setConstPosition(CONST_POSITION newConst);
    //CONST_POSITION getConstPosition();

    int child_id_increment = 0;

    void recursivePaint(QTransform transformSoFar, QPainter* painter, QString id, QDomElement el = QDomElement());

    QPainterPath parsePath(QString d);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    bool isTransparentPixel(QPointF pos) override;

    QRectF boundingRect() const override;

private:
    QDomDocument doc;

    QHash<QString, QDomElement> elements;

    QHash<QString, QPainterPath> paths;

    QMap<int,QList<int>> sprites;

    QList<int> currentFrames;

    int currentSprite = 1;

    int id = 0;

    QRectF actualBoundingRect;

    bool isSettingFrame = false;

    float width = 0;
    float height = 0;

    //CONST_POSITION posConst = CONST_POSITION::TOP;*/
};

#endif // ATLASCANVASOBJECT_H
