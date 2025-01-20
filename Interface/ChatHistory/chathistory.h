#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "../../canvasobject.h"
#include "../../widgets/scene.h"
#include "../Buttons/BlueRectButton/bluerectbutton.h"
#include "../SvgGridContainer/gridcontainer.h"
#include "../TextLabel/textlabel.h"
#include "chathistory_message.h"

class ChatHistory : public BlueRectButton
{
    Q_OBJECT
public:
    explicit ChatHistory(Scene* parent = nullptr);

    void addMessage(QString msg){
        if(historyBox != nullptr){
            QString storedMessage = msg;
            for(int i = pastMessages.size()-1; i >= 0; i--){
                TextLabel* label = pastMessages.at(i)->getLabel();
                QString oldLabel = label->getCurrentText();
                label->setText(storedMessage);
                storedMessage = oldLabel;
            }
        }
        return;
    }

protected:
    QVariant positionChanged(const QVariant& pos) override {
        QPointF point = pos.toPointF();
        double centerX = (scene->width()-boundingRect().width())/2;
        point.setX(boundingRect().width()+centerX);
        if(point.y() < 0+boundingRect().height()){
            point.setY(0+boundingRect().height());
            setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/arrows/up.svg");
        }else if(point.y() > maxHeight){
            point.setY(maxHeight);
            setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/arrows/down.svg");
        }
        return point;
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override {
        if(pos().y() >= maxHeight){
            QPointF point = pos();
            point.setY(-1+boundingRect().height());
            setPos(point);
        }else{
            QPointF point = pos();
            point.setY(maxHeight+1);
            setPos(point);
        }
    }

private:
    Scene* scene = nullptr;
    CanvasObject* historyBox = nullptr;
    QList<ChatHistory_Message*> pastMessages;
    double maxHeight = 0;

};

#endif // CHATHISTORY_H
