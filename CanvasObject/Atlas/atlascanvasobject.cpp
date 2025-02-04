#include "atlascanvasobject.h"

AtlasCanvasObject::AtlasCanvasObject(AtlasCanvasObject* parent) : AbstractCanvasObject(parent) {}

void AtlasCanvasObject::initFrames(QString filePath){
    if(filePath.isEmpty()) return;
    QList<CANVAS::Frame> arrays;
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
                            QList<CANVAS::Frame*> frames;
                            if(j->isObject()){
                                QJsonObject spriteObj = j->toObject();
                                for(auto k = spriteObj.begin(); k != spriteObj.end(); k++){
                                    int sprite = k.key().toInt();
                                    QJsonValueRef spriteValue = k.value();
                                    if(spriteValue.isArray()){
                                        QJsonArray frameArray = spriteValue.toArray();
                                        for(auto k = frameArray.begin(); k != frameArray.end(); k++){
                                            if(k->isObject()){
                                                QJsonObject frameObj = k->toObject();
                                                for(auto l = frameObj.begin(); l != frameObj.end(); l++){
                                                    int frame = l.key().toInt();
                                                    QJsonValueRef frameValue = l.value();
                                                    if(frameValue.isObject()){
                                                        QJsonObject frameObj = frameValue.toObject();
                                                        QJsonValue xminValue = frameObj["xmin"];
                                                        QJsonValue xmaxValue = frameObj["xmax"];
                                                        QJsonValue yminValue = frameObj["ymin"];
                                                        QJsonValue ymaxValue = frameObj["ymax"];
                                                        int xmin = 0;
                                                        int xmax = 0;
                                                        int ymin = 0;
                                                        int ymax = 0;
                                                        if(xminValue.isString()){
                                                            xmin = xminValue.toString().toInt();
                                                        }
                                                        if(yminValue.isString()){
                                                            ymin = yminValue.toString().toInt();
                                                        }
                                                        if(xmaxValue.isString()){
                                                            xmax = xmaxValue.toString().toInt();
                                                        }
                                                        if(ymaxValue.isString()){
                                                            ymax = ymaxValue.toString().toInt();
                                                        }
                                                        CANVAS::Frame* frame = new CANVAS::Frame;
                                                        frame->xmin = xmin;
                                                        frame->xmax = xmax;
                                                        frame->ymin = ymin;
                                                        frame->ymax = ymax;
                                                        frames.append(frame);
                                                    }
                                                }
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
                        renderer()->load(arr);
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
                        qDebug() << "FOUND THIS MANY " << elements.count();
                    }
                }
        }
    }
}

QList<CANVAS::Frame*>& AtlasCanvasObject::getCurrentSpriteFrames(){
    return this->currentFrames;
}

QMap<int, QList<CANVAS::Frame*>>& AtlasCanvasObject::getSprites(){
    return this->sprites;
}

QList<CANVAS::Frame*>& AtlasCanvasObject::setCurrentSprite(int sprite){
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
        QList<CANVAS::Frame*> map;
        map.append(new CANVAS::Frame);
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
        CANVAS::Frame frame = *currentFrames.at(currentFrame);
        clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
        setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
                        obj->setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=0;
            CANVAS::Frame frame = *currentFrames.at(currentFrame);
            clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
            setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
                            obj->setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
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
        CANVAS::Frame frame = *currentFrames.at(currentFrame);
        clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
        setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
                        obj->setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
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
        CANVAS::Frame frame = *currentFrames.at(currentFrame);
        clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
        setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
                        obj->setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=currentFrames.size()-1;
            CANVAS::Frame frame = *currentFrames.at(currentFrame);
            clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
            setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<AtlasCanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->clipRegion = QRect(frame.xmin,frame.ymin,frame.xmax-frame.xmin,frame.ymax-frame.ymin);
                            obj->setElementId("frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame));
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

QRegion AtlasCanvasObject::getClipRegion(){
    return this->clipRegion;
}

void AtlasCanvasObject::recursivePaint(QPainter* painter, QString id, QDomElement el){
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
    qDebug() << id << el.tagName();
    QString transform = element.attribute("transform");
    if(!transform.isEmpty()){
        QStringList matrix = transform.replace("matrix(","").replace(")","").split(", ");
        if(matrix.count() == 6){
            painter->setTransform(QTransform(matrix[0].toFloat(),matrix[1].toFloat(),matrix[2].toFloat(),matrix[3].toFloat(),matrix[4].toFloat(),matrix[5].toFloat()), true);
        }
    }

    if(element.hasAttribute("href")){
        qDebug() << "Found reference : " << element.attribute("href");
        QString reference = element.attribute("href").replace("#","");
        QDomElement foundElement = elements.value(reference);
        if(!foundElement.isNull()){
            qDebug() << "---------------";
            recursivePaint(painter,reference);
            qDebug() << "---------------";
        }
    }

    if(element.tagName() == "path"){
        qDebug() << "Found path";
        QPainterPath* path = parsePath(element.attribute("d"));
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
        painter->drawPath(*path);
        delete path;
    }

    QDomElement child = element.firstChildElement();
    while(!child.isNull()){
        QString transform = child.attribute("transform");
        if(!transform.isEmpty()){
            QStringList matrix = transform.replace("matrix(","").replace(")","").split(", ");
            if(matrix.count() == 6){
                painter->setTransform(QTransform(matrix[0].toFloat(),matrix[1].toFloat(),matrix[2].toFloat(),matrix[3].toFloat(),matrix[4].toFloat(),matrix[5].toFloat()), true);
            }
        }
        if(element.tagName() == "clipPath" && child.tagName() == "path"){
            QPainterPath* path = parsePath(child.attribute("d"));
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
            painter->setClipPath(*path);
            qDebug() << "Found clip path path" << path->elementCount();
            delete path;
        }
        if(element.tagName() == "g" && child.tagName() == "use"){
            qDebug() << "Found child reference : " << child.attribute("href");
            QString reference = child.attribute("href").replace("#","");
            QDomElement foundElement = elements.value(reference);
            if(!foundElement.isNull()){
                qDebug() << "---------------";
                recursivePaint(painter,reference);
                qDebug() << "---------------";
            }
        }
        if(child.hasChildNodes()){
            qDebug() << "Has child";
            for(int i = 0; i < child.childNodes().count(); i++){
                QDomNode node = child.childNodes().at(i);
                if(node.isElement()){
                    QDomElement nodeElement = node.toElement();
                    qDebug() << "---------------";
                    recursivePaint(painter, "", nodeElement);
                    qDebug() << "Child " << i << " : " << nodeElement.tagName() << nodeElement.attribute("id");
                    qDebug() << "---------------";
                }
            }
        }

        child = child.nextSiblingElement();
    }

    painter->restore();
}


QPainterPath* AtlasCanvasObject::parsePath(QString d){
    QPainterPath* path = new QPainterPath();
    if(d.isEmpty()){
        return path;
    }
    QString currentCommand;
    QStringList list = d.split(QRegularExpression(R"([\s|,])"));
    QList<int> points;
    for(int i = 0; i < list.count(); i++){
        float point;
        QString param = list.at(i);
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
        }
        point = param.toFloat();
        points.append(point);
        if(currentCommand == "m" && points.count() == 2){
            path->moveTo(points.at(0),points.at(1));
            points.clear();
        }else if(currentCommand == "l" && points.count() == 2){
            path->lineTo(points.at(0),points.at(1));
            points.clear();
        }else if(currentCommand == "q" && points.count() == 4){
            path->quadTo(points.at(0),points.at(1),points.at(2),points.at(3));
            points.clear();
        }
        if(param.contains("z",Qt::CaseInsensitive)){
            currentCommand = "z";
            param = param.replace("z","",Qt::CaseInsensitive);
            path->closeSubpath();
        }
    }
    return path;
}

void AtlasCanvasObject::paint(QPainter *painter,
                                    const QStyleOptionGraphicsItem *option,
                                    QWidget *widget){
    /*QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;

    QTransform transform = painter->transform();
    QImage img(1900,4000,QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);

    QPainter p(&img);
    renderer()->render(&p);
    p.end();
    if(!clipRegion.isNull()){
        qDebug() << "painting" << clipRegion << transform.map(clipRegion);
        //painter->setClipRegion(clipRegion);
    }else{
        qDebug() << "ITS NULL";
    }
    painter->drawImage(QRectF(0,0,1900,4000),img);

    QGraphicsSvgItem::paint(painter,&opts,widget);*/

    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;
    /*painter->translate(QPointF(50,50));
    QPainterPath path;
    path.moveTo(QPointF(11.35, -7.75));
    path.quadTo(16.0, -4.55,16,0);
    path.quadTo(16, 4.55, 11.35, 7.8);
    path.quadTo(6.65, 11.0, 0, 11.0);
    path.quadTo(-6.65, 11, -11.3, 7.8);
    path.quadTo(-16.0, 4.55, -16.0, 0);
    path.quadTo(-16, -4.55, -11.3, -7.75);
    path.quadTo(-6.65, -11.0, 0, -11.0);
    path.quadTo(6.65, -11, 11.35, -7.75);
    painter->setClipPath(path);
    painter->translate(QPointF(-50,-50));*/
    //painter->setClipRect(QRectF(25,25,25,25),Qt::ReplaceClip);
    painter->save();
    painter->setBrush(QColor("white"));
    painter->drawRect(QRect(0,0,100,100));
    painter->restore();
    qDebug() << "###########################";
    recursivePaint(painter,"frame-"+QString::number(currentSprite)+"-"+QString::number(currentFrame+1));
    qDebug() << "###########################";

    //QPainterPath path;
    /*path.moveTo(QPointF(19.375,36.7818));
    path.lineTo(QPointF(19.375,100.625));
    path.cubicTo(19.375,102.834,21.1659,104.625,23.375,104.625);
    path.lineTo(QPointF(87.2181,100.625));
    path.cubicTo(90.7818,104.625,92.5664,100.316,90.0466,97.7966);
    path.lineTo(26.2034,33.9534);
    path.cubicTo(23.6836,31.4336,19.375,33.2182,19.375,36.7818);*/
    /* RING path.moveTo(QPointF(11.35, -7.75));
    path.quadTo(16.0, -4.55,16,0);
    path.quadTo(16, 4.55, 11.35, 7.8);
    path.quadTo(6.65, 11.0, 0, 11.0);
    path.quadTo(-6.65, 11, -11.3, 7.8);
    path.quadTo(-16.0, 4.55, -16.0, 0);
    path.quadTo(-16, -4.55, -11.3, -7.75);
    path.quadTo(-6.65, -11.0, 0, -11.0);
    path.quadTo(6.65, -11, 11.35, -7.75);*/
    //path.closeSubpath();
    /*painter->save();

    //QRect rect(0,0,50,50);

    //ainter->setClipRegion(rect);
    painter->setClipRect(QRectF(25,25,25,25),Qt::ReplaceClip);

    painter->setBrush(QColor("red"));
    painter->setPen(QColor("white"));

    painter->drawRect(QRectF(0,0,100,100));

    painter->restore();*/

    //painter->translate(QPointF(10,0));
    //painter->restore();
    //QGraphicsSvgItem::paint(painter,&opts,widget);
}


QRectF AtlasCanvasObject::boundingRect() const {
    return QRectF(0,0,100,100);
}
