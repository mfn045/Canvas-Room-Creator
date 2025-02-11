#include "textlabelinput.h"

TextLabelInput::TextLabelInput(QWidget* parent) : QLabel(parent) {

}

void TextLabelInput::resizeEvent(QResizeEvent *event){
    this->width = event->size().width();
    this->height = event->size().height();
}

int TextLabelInput::getHeight(){
    return this->height;
}

int TextLabelInput::getWidth(){
    return this->width;
}
