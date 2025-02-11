#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QTextCursor>
#include "textlabelinput.h"

class TextLabel : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit TextLabel(QGraphicsItem* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool isAllowedCharacter(int c);

    QString getCurrentText();
    QString setText(QString text);

    void clearTextBox();

    int setTextLimit(int textLimit);
    int getTextLimit();

    TextLabelInput* getInput();

private:
    TextLabelInput* input = nullptr;
    int textLimit = -1;

private slots:
    void textChanged();
};

#endif // TEXTLABEL_H
