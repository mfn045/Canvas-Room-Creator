#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include <QTextLayout>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QTextCursor>

class TextBox : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit TextBox(QGraphicsItem* parent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool isAllowedCharacter(int c);

    QString getCurrentText();

    void clearTextBox();

    int setTextLimit(int textLimit);
    int getTextLimit();

    bool setCursorSetBeginning(bool CursorSetBeginning);
    bool getCursorSetBeginning();

    QTextEdit* getInput();

private:
    QTextEdit* input = nullptr;
    int textLimit = -1;
    bool cursorSetBeginning = false;

private slots:
    void textChanged();
};

#endif // TEXTBOX_H
