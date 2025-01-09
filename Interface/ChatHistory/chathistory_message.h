#ifndef CHATHISTORY_MESSAGE_H
#define CHATHISTORY_MESSAGE_H

#include "../../canvasobject.h"
#include "../TextLabel/textlabel.h"

class ChatHistory_Message : public CanvasObject
{
    Q_OBJECT
public:
    explicit ChatHistory_Message(CanvasObject* parent = nullptr);

    TextLabel* getLabel();

    void setHighlight();
    void remHighlight();

public slots:
    void hoverEnterReceiver(QPointF pos);
    void hoverLeaveReceiver(QPointF pos);


private:
    TextLabel* textLabel = nullptr;
    PROPERTIES* properties = nullptr;
    PROPERTIES* emptyProperties = nullptr;
};

#endif // CHATHISTORY_MESSAGE_H
