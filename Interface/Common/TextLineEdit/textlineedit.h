#ifndef TEXTLINEEDIT_H
#define TEXTLINEEDIT_H

#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QTextCursor>
#include "textlineeditinput.h"

class TextLineEdit : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit TextLineEdit(QGraphicsItem* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool isAllowedCharacter(int c);

    QString getCurrentText();
    QString setText(QString text);

    void clearTextBox();

    int setTextLimit(int textLimit);
    int getTextLimit();

    TextLineEditInput* getInput();

private:
    TextLineEditInput* input = nullptr;
    int textLimit = -1;

private slots:
    void textChanged();
};

#endif // TEXTLINEEDIT_H
