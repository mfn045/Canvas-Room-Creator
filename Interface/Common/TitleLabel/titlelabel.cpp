#include "titlelabel.h"

TitleLabel::TitleLabel(QGraphicsItem* parent) : QGraphicsItem(parent) {
}

QRectF TitleLabel::boundingRect() const {
    return this->rect;
}


QString TitleLabel::setText(QString text){
    this->text = text;
    path = QPainterPath();
    QFont font("CCComicrazyItalic",15);
    path.addText(QPoint(0,0),font,text);
    rect = path.boundingRect();
    return this->text;
}
QString TitleLabel::getText(){
    return this->text;
}


void TitleLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    QBrush brush = painter->brush();
    brush.setColor(QColor(0,51,102,255));
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

    QPen pen = painter->pen();
    pen.setColor(QColor(0,51,102,255));
    pen.setCapStyle(Qt::MPenCapStyle);
    pen.setJoinStyle(Qt::BevelJoin);
    pen.setWidthF(6.0f);
    painter->setPen(pen);

    painter->drawPath(path);
    painter->restore();

    painter->save();
    brush = painter->brush();
    brush.setColor(QColor("white"));
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

    pen = painter->pen();
    pen.setColor(QColor("white"));
    pen.setCapStyle(Qt::MPenCapStyle);
    pen.setJoinStyle(Qt::BevelJoin);
    pen.setWidthF(1.0f);
    painter->setPen(pen);

    painter->drawPath(path);
    painter->restore();
}
