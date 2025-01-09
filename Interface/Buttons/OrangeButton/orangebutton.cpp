#include "orangebutton.h"

OrangeButton::OrangeButton(CanvasObject* parent, SIZE size) : AbstractButton(parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    QString path = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/dialogs/buttons/orange/";

    if(size == SIZE::SMALL){
        path += "small";
    }else if(size == SIZE::MEDIUM){
        path += "medium";
    }else if(size == SIZE::LARGE){
        path += "large";
    }

    setIsHoverable(true);
    setIsClickable(true);

    setUp(path+"/up.svg");
    setDown(path+"/down.svg");
    setOver(path+"/over.svg");

    if(text == nullptr){
        text = new QGraphicsProxyWidget(this);
        text->setFlag(GraphicsItemFlag::ItemIsSelectable,false);
        text->setFlag(GraphicsItemFlag::ItemIsFocusable,false);
        text->setAcceptedMouseButtons(Qt::NoButton);
        text->setAcceptHoverEvents(false);
        text->setAcceptTouchEvents(false);
        textEdit = new QTextEdit();
        textEdit->setStyleSheet("background-color:transparent; border: none; padding-top:7px;");
        textEdit->setMinimumSize(QSize(boundingRect().width(),boundingRect().height()));
        textEdit->setMaximumSize(QSize(boundingRect().width(),boundingRect().height()));
        textEdit->setDisabled(true);
        text->setWidget(textEdit);
        text->setPos(QPointF(0,0));
    }

}

void OrangeButton::setText(QString msg){
    if(text == nullptr){
        text = new QGraphicsProxyWidget(this);
        text->setFlag(GraphicsItemFlag::ItemIsSelectable,false);
        text->setFlag(GraphicsItemFlag::ItemIsFocusable,false);
        text->setAcceptedMouseButtons(Qt::NoButton);
        text->setAcceptHoverEvents(false);
        text->setAcceptTouchEvents(false);
        textEdit = new QTextEdit();
        textEdit->setStyleSheet("background-color:transparent; border: none; padding:7px;");
        textEdit->resize(QSize(boundingRect().width(),boundingRect().height()));
        textEdit->setDisabled(true);
        text->setWidget(textEdit);
        text->setPos(QPointF(0,0));

        QFont font(textEdit->font());
        font.setFamily("Arial Narrow Bold");
        font.setPointSize(17);
        textEdit->setTextColor(QColor(255,255,255));
        textEdit->setFont(font);
        textEdit->setText(msg);
        textEdit->setAlignment(Qt::AlignCenter);
    }else{

        QFont font(textEdit->font());
        font.setFamily("Arial Narrow Bold");
        font.setPointSize(17);
        textEdit->setTextColor(QColor(255,255,255));
        textEdit->setFont(font);
        textEdit->setText(msg);
        textEdit->setAlignment(Qt::AlignCenter);
    }
    return;
}
