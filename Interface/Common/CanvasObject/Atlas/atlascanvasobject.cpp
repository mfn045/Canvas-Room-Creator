#include "atlascanvasobject.h"

AtlasCanvasObject::AtlasCanvasObject(AtlasCanvasObject* parent) : AbstractCanvasObject(parent) {}

void AtlasCanvasObject::initFrames(QString filePath){
    if(filePath.isEmpty()) return;
    QList<int> arrays;
    QDir directory(filePath);

    if(directory.exists()){
        qDebug() << "exists";
            QStringList list = directory.entryList();
            for(QString name : list){
                qDebug() << "FOUND " << name;
                if(name.endsWith(".json",Qt::CaseInsensitive)){
                    qDebug() << "ENDS WITH JSON : " << name;
                    QFile jsonFile(filePath + directory.separator() + name);
                    if(jsonFile.open(QFile::ReadOnly)){
                        qDebug() << "OPENED " << name;
                        QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
                        QJsonArray root = doc.array();
                        for(auto j = root.begin(); j != root.end(); j++){
                            QList<int> frames;
                            if(j->isObject()){
                                QJsonObject spriteObj = j->toObject();
                                for(auto k = spriteObj.begin(); k != spriteObj.end(); k++){
                                    int sprite = k.key().toInt();
                                    QJsonValueRef spriteValue = k.value();
                                    if(spriteValue.isArray()){
                                        QJsonArray frameArray = spriteValue.toArray();
                                        for(auto k = frameArray.begin(); k != frameArray.end(); k++){
                                            if(k->isString()){
                                                int frameNum = k->toInt();
                                                qDebug() << "added " << frameNum;
                                                frames.append(frameNum);
                                            }
                                        }
                                    }
                                    sprites.insert(sprite,frames);
                                }
                            }
                        }
                    }
                }else if(name.endsWith(".svg",Qt::CaseInsensitive)){
                    QFile svgFile(filePath + directory.separator() + name);
                    if(svgFile.open(QFile::ReadOnly)){
                        qDebug() << "OPENED SVG";
                        QByteArray arr = svgFile.readAll();
                        doc.setContent(arr);

                        QDomElement docElem = doc.documentElement();
                        qDebug() << docElem.tagName() << docElem.attribute("width") << docElem.attribute("height");

                        QDomElement child = docElem.firstChildElement();
                        QDomElement defs = docElem.firstChildElement("defs");
                        while(!child.isNull()){
                            QString id = child.attribute("id");
                            if(!id.isEmpty()){
                                elements.insert(id,child);
                            }
                            child = child.nextSiblingElement();
                        }
                        if(!defs.isNull()){
                            QDomElement defsChild = defs.firstChildElement();
                            while(!defsChild.isNull()){
                                QString id = defsChild.attribute("id");
                                if(!id.isEmpty()){
                                    elements.insert(id,defsChild);
                                }
                                defsChild = defsChild.nextSiblingElement();
                            }
                        }
                        doc.clear();
                        qDebug() << "FOUND THIS MANY " << elements.count();
                    }
                }
        }
    }
}

QList<int>& AtlasCanvasObject::getCurrentSpriteFrames(){
    return this->currentFrames;
}

QMap<int, QList<int>>& AtlasCanvasObject::getSprites(){
    return this->sprites;
}

QList<int>& AtlasCanvasObject::setCurrentSprite(int sprite){
    bool changed = false;
    isSettingFrame = true;
    for(auto i = sprites.begin(); i != sprites.end(); i++){
        if(i.key() == sprite){
            this->currentFrames = i.value();
            this->currentSprite = sprite;
            changed = true;
            qDebug() << "FOUND THE SPRITE FOR FUNCTION SETCURRENT SPRITE " << this->currentFrames.size();
        }
    }
    if(!changed){
        QList<int> map;
        this->currentFrames = map;
        this->currentSprite = -1;
    }
    isSettingFrame = false;
    return this->currentFrames;
}

int AtlasCanvasObject::getCurrentSprite(){
    return this->currentSprite;
}

void AtlasCanvasObject::nextFrame(bool loop, bool force){
    if(currentFrames.isEmpty()) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(!animationOn) return;
    if(currentFrame < currentFrames.size()-1){
        currentFrame++;
        update();
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->update();
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=0;
            update();
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->update();
                        }
                    }
                }
            }
            isImageLatest = false;
        }else{
            emit animationDone();
        }
    }
}

void AtlasCanvasObject::setFrame(int currentFrame){
    if(currentFrames.isEmpty()) return;
    if(currentFrame < currentFrames.size() && currentFrame >= 0){
        this->currentFrame = currentFrame;
        update();
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->update();
                    }
                }
            }
        }
        isImageLatest = false;
    }
}

void AtlasCanvasObject::prevFrame(bool loop, bool force){
    if(currentFrames.isEmpty()) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(!animationOn) return;
    if(currentFrame > 0){
        currentFrame--;
        update();
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->update();
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=currentFrames.size()-1;
            update();
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->update();
                        }
                    }
                }
            }
            isImageLatest = false;
        }else{
            emit animationDone();
        }
    }
}

void AtlasCanvasObject::recursivePaint(QTransform originalPainterTransform, QPainter* painter, QString id, QDomElement el){
    painter->save();
    QDomElement& element = el;
    if(!id.isEmpty()){
        element = elements.value(id);
    } else if(!el.isNull()){
        element = el;
    }else{
        qDebug() << "ID and QDomElement parameters can't be both empty and null!";
        return;
    }
    QString transform = element.attribute("transform");
    if(!transform.isEmpty()){
        QStringList matrix = transform.replace("matrix(","").replace(")","").split(", ");
        if(matrix.count() == 6){
            QTransform t = QTransform(matrix[0].toFloat(),matrix[1].toFloat(),matrix[2].toFloat(),matrix[3].toFloat(),matrix[4].toFloat(),matrix[5].toFloat());
            painter->setTransform(t, true);
        }
    }

    if(element.hasAttribute("href")){
        QString reference = element.attribute("href").replace("#","");
        QDomElement foundElement = elements.value(reference);
        if(!foundElement.isNull()){
            recursivePaint(originalPainterTransform,painter,reference);
        }
    }

    if(element.tagName() == "path"){
        QString draw = element.attribute("d");
        QPainterPath path;
        if(paths.contains(draw)){
            path = paths.value(draw);
        }else{
            paths.insert(draw,parsePath(element.attribute("d")));
            path = paths.value(draw);
        }
        QString fill = element.attribute("fill");
        QString fillOpacity = element.attribute("fill-opacity");
        QString stroke = element.attribute("stroke");
        QString strokeLineCap = element.attribute("stroke-linecap");
        QString strokeLineJoin = element.attribute("stroke-linejoin");
        QString strokeWidth = element.attribute("stroke-width");
        if(!fill.isEmpty() && !fill.contains("none",Qt::CaseInsensitive)){
            painter->setBrush(QColor(fill));
        }
        if(!fillOpacity.isEmpty() && !fillOpacity.contains("none",Qt::CaseInsensitive)){
            painter->setOpacity(fillOpacity.toFloat());
        }
        if(!stroke.isEmpty() && !stroke.contains("none",Qt::CaseInsensitive)){
            QPen pen = painter->pen();
            pen.setColor(QColor(stroke));
            if(!strokeLineCap.isEmpty() && !stroke.contains("none",Qt::CaseInsensitive)){
                if(strokeLineCap == "round"){
                    pen.setCapStyle(Qt::RoundCap);
                } else if(strokeLineCap == "square"){
                    pen.setCapStyle(Qt::RoundCap);
                }
            }
            if(!strokeLineJoin.isEmpty() && !strokeLineJoin.contains("none",Qt::CaseInsensitive)){
                if(strokeLineJoin == "round"){
                    pen.setJoinStyle(Qt::RoundJoin);
                } else if(strokeLineJoin == "bevel"){
                    pen.setJoinStyle(Qt::BevelJoin);
                } else if(strokeLineJoin == "miter"){
                    pen.setJoinStyle(Qt::MiterJoin);
                }
            }
            if(!strokeWidth.isEmpty() && !strokeWidth.contains("none",Qt::CaseInsensitive)){
                pen.setWidthF(strokeWidth.toFloat());
            }
            painter->setPen(pen);
        } else {
            painter->setPen(Qt::NoPen);
        }
        QTransform t = painter->transform();
        t *= originalPainterTransform.inverted();
        actualBoundingRect = actualBoundingRect.united(t.mapRect(path.boundingRect()));
        painter->drawPath(path);
    }

    QDomElement child = element.firstChildElement();
    while(!child.isNull()){
        QString transform = child.attribute("transform");
        if(!transform.isEmpty()){
            QStringList matrix = transform.replace("matrix(","").replace(")","").split(", ");
            if(matrix.count() == 6){
                QTransform t = QTransform(matrix[0].toFloat(),matrix[1].toFloat(),matrix[2].toFloat(),matrix[3].toFloat(),matrix[4].toFloat(),matrix[5].toFloat());
                painter->setTransform(t, true);
            }
        }
        if(element.tagName() == "clipPath" && child.tagName() == "path"){
            QPainterPath path = parsePath(child.attribute("d"));
            QString fill = child.attribute("fill");
            QString fillOpacity = child.attribute("fill-opacity");
            QString stroke = child.attribute("stroke");
            QString strokeLineCap = child.attribute("stroke-linecap");
            QString strokeLineJoin = child.attribute("stroke-linejoin");
            QString strokeWidth = child.attribute("stroke-width");
            if(!fill.isEmpty() && !fill.contains("none",Qt::CaseInsensitive)){
                painter->setBrush(QColor(fill));
            }
            if(!fillOpacity.isEmpty() && !fillOpacity.contains("none",Qt::CaseInsensitive)){
                painter->setOpacity(fillOpacity.toFloat());
            }
            if(!stroke.isEmpty() && !stroke.contains("none",Qt::CaseInsensitive)){
                QPen pen = painter->pen();
                pen.setColor(QColor(stroke));
                if(!strokeLineCap.isEmpty() && !stroke.contains("none",Qt::CaseInsensitive)){
                    if(strokeLineCap == "round"){
                        pen.setCapStyle(Qt::RoundCap);
                    } else if(strokeLineCap == "square"){
                        pen.setCapStyle(Qt::RoundCap);
                    }
                    painter->setPen(pen);
                }
                if(!strokeLineJoin.isEmpty() && !strokeLineJoin.contains("none",Qt::CaseInsensitive)){
                    if(strokeLineJoin == "round"){
                        pen.setJoinStyle(Qt::RoundJoin);
                    } else if(strokeLineJoin == "bevel"){
                        pen.setJoinStyle(Qt::BevelJoin);
                    } else if(strokeLineJoin == "miter"){
                        pen.setJoinStyle(Qt::MiterJoin);
                    }
                    painter->setPen(pen);
                }
                if(!strokeWidth.isEmpty() && !strokeWidth.contains("none",Qt::CaseInsensitive)){
                    pen.setWidthF(strokeWidth.toFloat());
                    painter->setPen(pen);
                }
                painter->setPen(pen);
            } else {
                painter->setPen(Qt::NoPen);
            }
            painter->setClipPath(path);
        }
        if(element.tagName() == "g" && child.tagName() == "use"){
            QString reference = child.attribute("href").replace("#","");
            QDomElement foundElement = elements.value(reference);
            if(!foundElement.isNull()){
                recursivePaint(originalPainterTransform,painter,reference);
            }
        }
        if(child.hasChildNodes()){
            for(int i = 0; i < child.childNodes().count(); i++){
                QDomNode node = child.childNodes().at(i);
                if(node.isElement()){
                    QDomElement nodeElement = node.toElement();
                    recursivePaint(originalPainterTransform,painter, "", nodeElement);
                }
            }
        }

        child = child.nextSiblingElement();
    }

    painter->restore();
}


QPainterPath AtlasCanvasObject::parsePath(QString d){
    QPainterPath path;
    if(d.isEmpty()){
        return path;
    }
    QString currentCommand;
    QStringList list = d.split(QRegularExpression(R"([\s|,])"));
    QList<float> points;
    for(int i = 0; i < list.count(); i++){
        float point;
        QString param = list.at(i);
        bool closeLine = false;
        if(param.toLower() == "m"){
            currentCommand = "m";
            points.clear();
            continue;
        } else if(param.contains("m",Qt::CaseInsensitive)){
            currentCommand = "m";
            param = param.replace("m","",Qt::CaseInsensitive);
            points.clear();
        } else if(param.toLower() == "l"){
            currentCommand = "l";
            points.clear();
            continue;
        } else if(param.contains("l",Qt::CaseInsensitive)){
            currentCommand = "l";
            param = param.replace("l","",Qt::CaseInsensitive);
            points.clear();
        } else if(param.toLower() == "q"){
            currentCommand = "q";
            points.clear();
            continue;
        } else if(param.contains("q",Qt::CaseInsensitive)){
            currentCommand = "q";
            param = param.replace("q","",Qt::CaseInsensitive);
            points.clear();
        } else if(param.endsWith("z",Qt::CaseInsensitive)){
            param = param.replace("z","",Qt::CaseInsensitive);
            closeLine = true;
        }
        if(!param.isEmpty()){
            point = param.toFloat();
            points.append(point);
        }
        if(currentCommand == "m" && points.count() == 2){
            path.moveTo(points.at(0),points.at(1));
            points.clear();
        }else if(currentCommand == "l" && points.count() == 2){
            path.lineTo(points.at(0),points.at(1));
            points.clear();
        }else if(currentCommand == "q" && points.count() == 4){
            path.quadTo(points.at(0),points.at(1),points.at(2),points.at(3));
            points.clear();
        }
        if(closeLine){
            currentCommand = "z";
            path.closeSubpath();
        }
    }
    return path;
}

bool AtlasCanvasObject::isTransparentPixel(QPointF pos){
    if(actualBoundingRect.contains(QRectF(pos.x(),pos.y(),1,1))){
        return false;
    }
    return true;
}

void AtlasCanvasObject::paint(QPainter *painter,
                                    const QStyleOptionGraphicsItem *option,
                                    QWidget *widget){

    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;

    painter->save();
    painter->setBrush(QColor("red"));
    painter->drawRect(actualBoundingRect);
    painter->restore();
    actualBoundingRect = QRectF();
    recursivePaint(painter->transform(),painter,"frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame+1));
}


QRectF AtlasCanvasObject::boundingRect() const {
    return QRectF(0,0,100,100);
}
