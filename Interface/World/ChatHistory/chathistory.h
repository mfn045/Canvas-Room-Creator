#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "AbstractQtWidgets/scene.h"
#include "Interface/Widgets/Buttons/BlueRectButton/bluerectbutton.h"
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Common/TextLabel/textlabel.h"
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
                QFont font = label->font();
                font.setFamily("Burbank Small Medium");
                label->setFont(font);
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
            AssetsManager* am = AssetsManager::getInstance();
            setIcon(am->getAssetPath("interface.icons.arrows.up"));
        }else if(point.y() > maxHeight){
            point.setY(maxHeight);
            AssetsManager* am = AssetsManager::getInstance();
            setIcon(am->getAssetPath("interface.icons.arrows.up"));
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
    MultiCanvasObject* historyBox = nullptr;
    QList<ChatHistory_Message*> pastMessages;
    double maxHeight = 0;

};

#endif // CHATHISTORY_H
