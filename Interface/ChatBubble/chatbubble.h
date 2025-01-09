#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>
#include "../../canvasobject.h"
#include "../TextLabel/textlabel.h"

class ChatBubble : public CanvasObject
{
    Q_OBJECT
public:
    explicit ChatBubble(CanvasObject* parent, QString msg);

    enum TYPE {
        SMALL,
        MEDIUM,
        LARGE
    };

    void setText(QString msg);

private:
    const QString chatbubble_small = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chatbubble/1.svg";
    const QString chatbubble_medium = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chatbubble/2.svg";
    const QString chatbubble_large = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chatbubble/3.svg";

    TextLabel* bubbleTextLabel = nullptr;

    QString bubbleMsg = "";

    TYPE bubbleType = SMALL;

    QTimer timer;
};

#endif // CHATBUBBLE_H
