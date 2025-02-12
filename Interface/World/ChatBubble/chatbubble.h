#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/TextLabel/textlabel.h"

class ChatBubble : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit ChatBubble(MultiCanvasObject* parent, QString msg);

    enum TYPE {
        SMALL,
        MEDIUM,
        LARGE
    };

    void setText(QString msg);

private:
    const QString chatbubble_small = AssetsManager::getInstance()->getAssetPath("interface.world.chatbubble.1");
    const QString chatbubble_medium = AssetsManager::getInstance()->getAssetPath("interface.world.chatbubble.2");
    const QString chatbubble_large = AssetsManager::getInstance()->getAssetPath("interface.world.chatbubble.3");

    TextLabel* bubbleTextLabel = nullptr;

    QString bubbleMsg = "";

    TYPE bubbleType = SMALL;

    QTimer timer;
};

#endif // CHATBUBBLE_H
