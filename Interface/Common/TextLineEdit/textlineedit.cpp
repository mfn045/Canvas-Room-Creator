#include "textlineedit.h"

TextLineEdit::TextLineEdit(QGraphicsItem* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    setContentsMargins(0,0,0,0);
    input = new TextLineEditInput();
    input->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    input->setContentsMargins(0,0,0,0);
    input->setStyleSheet("background-color:transparent; border: none; margin:0; padding: 0; color:black;");
    //connect(input,SIGNAL(textChanged()),this,SLOT(textChanged()));
    setWidget(input);
}


void TextLineEdit::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget){
    if(painter && option && widget){
        if(!painter->isActive()) return;
        QStyleOptionGraphicsItem opts(*option);

        opts.state = QStyle::State_None;

        painter->setBrush(Qt::NoBrush);

        QPen pen = painter->pen();
        pen.setBrush(QColor(0,51,102,255));
        pen.setWidth(2);
        painter->setPen(pen);

        return QGraphicsProxyWidget::paint(painter, &opts, widget);
    }
    return;
}


bool TextLineEdit::isAllowedCharacter(int c){
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

QString TextLineEdit::getCurrentText(){
    return this->input->text();
}

QString TextLineEdit::setText(QString text){
    this->input->setText(text);
    this->input->adjustSize();
    return text;
}

TextLineEditInput* TextLineEdit::getInput(){
    return this->input;
}

void TextLineEdit::clearTextBox(){
    input->clear();
}


int TextLineEdit::setTextLimit(int textLimit){
    this->textLimit = textLimit;
    return this->textLimit;
}
int TextLineEdit::getTextLimit(){
    return this->textLimit;
}


void TextLineEdit::textChanged(){
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
