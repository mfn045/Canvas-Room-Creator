#include "textinput.h"

TextInput::TextInput(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.widgets.inputs.textinput");
    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);

    lineedit = new TextLineEdit(this);
    lineedit->setMaximumSize(QSize(boundingRect().width()-4,boundingRect().height()));
    lineedit->setMinimumSize(QSize(boundingRect().width()-4,boundingRect().height()));
    lineedit->setTextLimit(14);
    lineedit->setPos(QPointF(4,0));
}

TextLineEdit* TextInput::getLineEdit(){
    return this->lineedit;
}
