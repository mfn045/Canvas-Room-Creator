#include "textlabel.h"

TextLabel::TextLabel(QGraphicsItem* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    setContentsMargins(0,0,0,0);
    input = new TextLabelInput();
    input->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    input->setIndent(0);
    input->setMargin(0);
    input->setContentsMargins(0,0,0,0);
    input->setWordWrap(true);
    input->setStyleSheet("background-color:transparent; border: none; margin:0; padding: 0; color:black;");
    connect(input,SIGNAL(textChanged()),this,SLOT(textChanged()));
    setWidget(input);
}


void TextLabel::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option,
                    QWidget *widget){
    if(painter && option && widget){
        if(!painter->isActive()) return;
        QStyleOptionGraphicsItem opts(*option);

        opts.state = QStyle::State_None;

        painter->setBrush(Qt::NoBrush);
        painter->setPen(Qt::NoPen);

        return QGraphicsProxyWidget::paint(painter, &opts, widget);
    }
    return;
}


bool TextLabel::isAllowedCharacter(int c){
    if(c >= 48 && c <= 57){
        return true;
    }else if(c >= 65 && c <= 90){
        return true;
    }else if(c >= 97 && c <= 122){
        return true;
    } else if(c == 39 || c== 33 || c==34 || c==63 || c == 32){
        return true;
    }
    return false;
}

QString TextLabel::getCurrentText(){
    return this->input->text();
}

QString TextLabel::setText(QString text){
    this->input->setText(text);
    this->input->adjustSize();
    return text;
}

TextLabelInput* TextLabel::getInput(){
    return this->input;
}

void TextLabel::clearTextBox(){
    input->clear();
}


int TextLabel::setTextLimit(int textLimit){
    this->textLimit = textLimit;
    return this->textLimit;
}
int TextLabel::getTextLimit(){
    return this->textLimit;
}


void TextLabel::textChanged(){
    if(textLimit != -1 && textLimit > 1 && input->text().size() > textLimit){
        QString msg = getCurrentText().first(textLimit);
        input->setText(msg);
    }
    input->adjustSize();
    adjustSize();
    input->updateGeometry();
    updateGeometry();
    input->update();
    update();
}
