#include "textlineeditinput.h"

TextLineEditInput::TextLineEditInput(QWidget* parent) : QLineEdit(parent) {

}

void TextLineEditInput::resizeEvent(QResizeEvent *event){
    this->width = event->size().width();
    this->height = event->size().height();
}

int TextLineEditInput::getHeight(){
    return this->height;
}

int TextLineEditInput::getWidth(){
    return this->width;
}
