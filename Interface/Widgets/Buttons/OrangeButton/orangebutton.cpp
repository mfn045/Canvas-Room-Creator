#include "orangebutton.h"

OrangeButton::OrangeButton(MultiCanvasObject* parent, SIZE size) : AbstractButton(parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }

    setIsHoverable(true);
    setIsClickable(true);


    AssetsManager* am = AssetsManager::getInstance();
    if(size == SIZE::SMALL){
        setUp(am->getAssetPath("interface.widgets.buttons.orangebutton.small.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.orangebutton.small.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.orangebutton.small.over"));
    }else if(size == SIZE::MEDIUM){
        setUp(am->getAssetPath("interface.widgets.buttons.orangebutton.medium.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.orangebutton.medium.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.orangebutton.medium.over"));
    }else if(size == SIZE::LARGE){
        setUp(am->getAssetPath("interface.widgets.buttons.orangebutton.large.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.orangebutton.large.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.orangebutton.large.over"));
    }


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
