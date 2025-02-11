#ifndef TITLELABEL_H
#define TITLELABEL_H

#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QFont>
#include <QPainter>

class TitleLabel : public QGraphicsItem
{
public:
    explicit TitleLabel(QGraphicsItem* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QRectF boundingRect() const override;

    QString setText(QString text);
    QString getText();


private:
    QString text = "";
    QPainterPath path;
    QRectF rect;
};

#endif // TITLELABEL_H
