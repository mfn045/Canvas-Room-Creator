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

    QRegion getClipRegion();

    QList<CANVAS::Frame*>& getCurrentSpriteFrames();

    QMap<int, QList<CANVAS::Frame*>>& getSprites();
    QList<CANVAS::Frame*>& setCurrentSprite(int sprite);
    int getCurrentSprite();

    void nextFrame(bool loop = true, bool force = false) override;
    void setFrame(int currentFrame) override;
    void prevFrame(bool loop = true, bool force = false) override;

    QPointF getOrigin();
    QPointF setOrigin(QPointF origin);

    //CONST_POSITION setConstPosition(CONST_POSITION newConst);
    //CONST_POSITION getConstPosition();

    int child_id_increment = 0;

    void recursivePaint(QPainter* painter, QString id, QDomElement el = QDomElement());

    QPainterPath* parsePath(QString d);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    QRectF boundingRect() const override;

private:
    QDomDocument doc;

    QHash<QString, QDomElement> elements;

    QMap<int,QList<CANVAS::Frame*>> sprites;

    QList<CANVAS::Frame*> currentFrames;

    int currentSprite = 1;

    int id = 0;

    QString name = "";

    QPointF origin;

    QRegion clipRegion;

    bool isSettingFrame = false;

    float width = 0;
    float height = 0;

    //CONST_POSITION posConst = CONST_POSITION::TOP;*/
};

#endif // ATLASCANVASOBJECT_H
