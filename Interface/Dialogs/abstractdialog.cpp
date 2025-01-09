#include "abstractdialog.h"

AbstractDialog::AbstractDialog(Scene* parent, TYPE type) {
    if(parent != nullptr){
        this->scene = parent;
    }

    setGridSize(43.7);
    setType(type);

}


float AbstractDialog::getGridSize(){
    return this->gridSize;
}
float AbstractDialog::setGridSize(float gridSize){
    this->gridSize = gridSize;
    return this->gridSize;
}


AbstractDialog::TYPE AbstractDialog::getType(){
    return this->type;
}

AbstractDialog::TYPE AbstractDialog::setType(TYPE type){
    this->type = type;
    const QString prefix = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/dialogs/grid";

    QString path_top = prefix;
    QString path_top_left = prefix;
    QString path_top_right = prefix;
    QString path_left = prefix;
    QString path_bottom = prefix;
    QString path_bottom_left = prefix;
    QString path_bottom_right = prefix;
    QString path_right = prefix;
    QString path_center = prefix;

    if(type == TYPE::BLUE){
        path_top += "/blue";
        path_top_left += "/blue";
        path_top_right += "/blue";
        path_left += "/blue";
        path_bottom += "/blue";
        path_bottom_left += "/blue";
        path_bottom_right += "/blue";
        path_right += "/blue";
        path_center += "/blue";
    }else if(type == TYPE::ORANGE){
        path_top += "/orange";
        path_top_left += "/orange";
        path_top_right += "/orange";
        path_left += "/orange";
        path_bottom += "/orange";
        path_bottom_left += "/orange";
        path_bottom_right += "/orange";
        path_right += "/orange";
        path_center += "/orange";
    }
    const QString top_suffix = "/top.svg";
    const QString top_left_suffix = "/top_left.svg";
    const QString top_right_suffix = "/top_right.svg";
    const QString left_suffix = "/left.svg";
    const QString bottom_suffix = "/bottom.svg";
    const QString bottom_left_suffix = "/bottom_left.svg";
    const QString bottom_right_suffix = "/bottom_right.svg";
    const QString right_suffix = "/right.svg";
    const QString center_suffix = "/center.svg";

    path_top += top_suffix;
    path_top_left += top_left_suffix;
    path_top_right += top_right_suffix;
    path_left += left_suffix;
    path_bottom += bottom_suffix;
    path_bottom_left += bottom_left_suffix;
    path_bottom_right += bottom_right_suffix;
    path_right += right_suffix;
    path_center += center_suffix;

    this->path_top = path_top;
    this->path_top_left = path_top_left;
    this->path_top_right = path_top_right;

    this->path_bottom = path_bottom;
    this->path_bottom_left = path_bottom_left;
    this->path_bottom_right = path_bottom_right;

    this->path_center = path_center;
    this->path_left = path_left;
    this->path_right = path_right;

    return this->type;
}

AbstractDialog::BUTTONS_LAYOUT AbstractDialog::getButtonsLayout() const{
    return this->buttonsLayout;
}

AbstractDialog::BUTTONS_LAYOUT AbstractDialog::setButtonsLayout(BUTTONS_LAYOUT buttonsLayout){
    this->buttonsLayout = buttonsLayout;
    return this->buttonsLayout;
}


int AbstractDialog::getRow(){
    return this->row;
}

int AbstractDialog::setRow(int row){
    this->row = row;
    return this->row;
}

int AbstractDialog::getCol(){
    return this->col;
}

int AbstractDialog::setCol(int col){
    this->col = col;
    return this->col;
}

bool AbstractDialog::init(){
    float farthest_x = 0;
    float farthest_y = 0;

    for(int j = 0; j < row; j++){
        for(int k = 0; k < col; k++){
            if(j == 0 && k == 0){
                PROPERTIES* top_left_properties = new PROPERTIES();
                top_left_properties->filePath = path_top_left;
                top_left = new CanvasObject();
                top_left->initFrames(top_left_properties->filePath,top_left_properties);
                top_left->setCurrentFrames(top_left_properties);
                top_left->setFrame(0);
                top_left->setParentItem(this);
                top_left->setZValue(0);
                top_left->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(j == 0 && k != 0 && k != col-1){
                // TOP
                PROPERTIES* top_properties = new PROPERTIES();
                top_properties->filePath = path_top;
                top = new CanvasObject();
                top->initFrames(top_properties->filePath,top_properties);
                top->setCurrentFrames(top_properties);
                top->setFrame(0);
                top->setParentItem(this);
                top->setZValue(0);
                top->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(j == 0 && k == col-1){
                // TOP RIGHT
                PROPERTIES* top_right_properties = new PROPERTIES();
                top_right_properties->filePath = path_top_right;
                top_right = new CanvasObject();
                top_right->initFrames(top_right_properties->filePath,top_right_properties);
                top_right->setCurrentFrames(top_right_properties);
                top_right->setFrame(0);
                top_right->setParentItem(this);
                top_right->setZValue(0);
                top_right->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(k == 0 && j != 0 && j != row-1){
                // LEFT
                PROPERTIES* left_properties = new PROPERTIES();
                left_properties->filePath = path_left;
                left = new CanvasObject();
                left->initFrames(left_properties->filePath,left_properties);
                left->setCurrentFrames(left_properties);
                left->setFrame(0);
                left->setParentItem(this);
                left->setZValue(0);
                left->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(k == col-1 && j != 0 && j != row-1){
                // RIGHT
                PROPERTIES* right_properties = new PROPERTIES();
                right_properties->filePath = path_right;
                right = new CanvasObject();
                right->initFrames(right_properties->filePath,right_properties);
                right->setCurrentFrames(right_properties);
                right->setFrame(0);
                right->setParentItem(this);
                right->setZValue(0);
                right->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(j == row-1 && k == 0){
                // BOTTOM LEFT
                PROPERTIES* bottom_left_properties = new PROPERTIES();
                bottom_left_properties->filePath = path_bottom_left;
                bottom_left = new CanvasObject();
                bottom_left->initFrames(bottom_left_properties->filePath,bottom_left_properties);
                bottom_left->setCurrentFrames(bottom_left_properties);
                bottom_left->setFrame(0);
                bottom_left->setParentItem(this);
                bottom_left->setZValue(0);
                bottom_left->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(j == row-1 && k != 0 && k != col-1){
                // BOTTOM
                PROPERTIES* bottom_properties = new PROPERTIES();
                bottom_properties->filePath = path_bottom;
                bottom = new CanvasObject();
                bottom->initFrames(bottom_properties->filePath,bottom_properties);
                bottom->setCurrentFrames(bottom_properties);
                bottom->setFrame(0);
                bottom->setParentItem(this);
                bottom->setZValue(0);
                bottom->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else if(j == row-1 && k == col-1){
                // BOTTOM RIGHT
                PROPERTIES* bottom_right_properties = new PROPERTIES();
                bottom_right_properties->filePath = path_bottom_right;
                bottom_right = new CanvasObject();
                bottom_right->initFrames(bottom_right_properties->filePath,bottom_right_properties);
                bottom_right->setCurrentFrames(bottom_right_properties);
                bottom_right->setFrame(0);
                bottom_right->setParentItem(this);
                bottom_right->setZValue(0);
                bottom_right->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            } else {
                // CENTER
                PROPERTIES* center_properties = new PROPERTIES();
                center_properties->filePath = path_center;
                center = new CanvasObject();
                center->initFrames(center_properties->filePath,center_properties);
                center->setCurrentFrames(center_properties);
                center->setFrame(0);
                center->setParentItem(this);
                center->setZValue(0);
                center->setPos(QPointF(gridSize*k,gridSize*j));
                if(gridSize*k > farthest_x){
                    farthest_x = gridSize*k;
                }
                if(gridSize*j > farthest_y){
                    farthest_y = gridSize*j;
                }
            }
        }
    }
    update();
    return true;
}


TextLabel* AbstractDialog::insertText(QString text){
    TextLabel* tb = new TextLabel(this);
    tb->setTextLimit(48);
    tb->setZValue(10);
    QFont font(tb->getInput()->font());
    font.setFamily("Arial");
    font.setPointSize(16);
    tb->getInput()->setFont(font);
    tb->getInput()->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    tb->setText(text);
    this->textLabels.append(tb);
    return tb;
}

AbstractButton* AbstractDialog::addButton(QString buttonName){
    if(getType() == TYPE::BLUE){
        BlueButton* button = new BlueButton(this);
        button->setZValue(10);
        button->setText(buttonName);
        buttons.append(button);
        return button;
    }else if(getType() == TYPE::ORANGE){
        OrangeButton* button = new OrangeButton(this);
        button->setZValue(10);
        button->setText(buttonName);
        buttons.append(button);
        return button;
    }
    return nullptr;
}


void AbstractDialog::setElementsPositions(float& elementsHeight, float& buttonsWidth) const{
    float outerMostX = 0;
    float outerMostY = (boundingRect().height()-elementsHeight)/2;

    if(!textLabels.isEmpty()){
        for(int i = 0; i < textLabels.size(); i++){
            TextLabel* tb = textLabels.at(i);
            tb->getInput()->setMinimumWidth(boundingRect().width()-outter_paddingX*2);
            tb->getInput()->setMaximumWidth(boundingRect().width()-outter_paddingX*2);
            tb->getInput()->adjustSize();
            float centerX = (boundingRect().width() - tb->getInput()->size().width())/2;
            tb->setPos(QPointF(centerX,outerMostY));
            outerMostY += tb->getInput()->getHeight() + element_spacingY;
        }
    }

    if(getButtonsLayout() == BUTTONS_LAYOUT::HORIZONTAL){
        //button_x_spacing = (boundingRect().width()-(outter_padding*2)-(button_width*buttons.size()))/(buttons.size()+1);
        float button_width = 0;
        float centerX_ForButtons = (boundingRect().width() - buttonsWidth)/2;
        for(int i = 0; i < buttons.size(); i++){
            AbstractButton* button = buttons.at(i);
            if(i == 0){
                button_width = button->boundingRect().width();
                outerMostX += centerX_ForButtons;
            }
            //outerMostX = outter_paddingX+button_spacingXY+((button_width+button_spacingXY)*i); ( Older positioning of X-axis for buttons)
            button->setPos(QPointF(outerMostX,outerMostY));
            if(i == buttons.size()-1){
                outerMostX += button_width;
            }else{
                outerMostX += button_width+button_spacingXY;
            }
        }
    } else if(getButtonsLayout() == BUTTONS_LAYOUT::VERTICAL){
        for(int i = 0; i < buttons.size(); i++){
            AbstractButton* button = buttons.at(i);
            float centerX = (boundingRect().width() - button->boundingRect().width())/2;
            button->setPos(QPointF(centerX,outerMostY));
            outerMostY += button->boundingRect().height() + button_spacingXY;
        }
    }
}

void AbstractDialog::setDialogPosition(){
    qreal dialogWidth = boundingRect().width();
    qreal sceneWidth = getScene()->sceneRect().width();
    qreal dialogXSpacing = (sceneWidth-dialogWidth)/2;
    qreal dialogHeight = boundingRect().height();
    qreal sceneHeight = getScene()->sceneRect().height();
    qreal dialogYSpacing = (sceneHeight-dialogHeight)/2;
    setPos(QPointF(dialogXSpacing,dialogYSpacing));
}

QList<float> AbstractDialog::approximateMeasurements() const{
    float outerMostY = 0;
    float outerMostX = 0;
    float elementsHeight = 0;
    outerMostY+=element_spacingY;
    if(!textLabels.isEmpty()){
        for(TextLabel* tb : textLabels){
            outerMostY += tb->getInput()->getHeight() + element_spacingY;
            elementsHeight += tb->getInput()->getHeight() + element_spacingY;
            float newOuterMostX = (outter_paddingX*2)+tb->getInput()->getWidth();
            if(newOuterMostX > outerMostX){
                outerMostX = newOuterMostX;
            }
        }
    }
    float buttons_width = 0;
    float button_width = 0;
    float button_height = 0;
    if(getButtonsLayout() == BUTTONS_LAYOUT::HORIZONTAL){
        for(int i = 0; i < buttons.size(); i++){
            if(i == 0){
                AbstractButton* button = buttons.at(i);
                button_width = button->boundingRect().width();
                button_height = button->boundingRect().height();
                outerMostY += button_height;
                elementsHeight += button_height;
            }
            float newOuterMostX = 0;
            if(i == buttons.size()-1){
                newOuterMostX = ((outter_paddingX*2)+button_width)+((button_width+button_spacingXY)*(i-1))+button_width;
                buttons_width += button_width;
            }else{
                newOuterMostX = ((outter_paddingX*2)+button_width)+((button_width+button_spacingXY)*i);
                buttons_width += button_width+button_spacingXY;
            }
            if(newOuterMostX > outerMostX){
                outerMostX = newOuterMostX;
            }
        }
    } else if(getButtonsLayout() == BUTTONS_LAYOUT::VERTICAL){
        for(int i = 0; i < buttons.size(); i++){
            if(i == 0){
                AbstractButton* button = buttons.at(i);
                button_width = button->boundingRect().width();
                button_height = button->boundingRect().height();
            }
            float newOuterMostX = (outter_paddingX*2)+button_width;
            if(newOuterMostX > outerMostX){
                outerMostX = newOuterMostX;
            }
            if(i == buttons.size()-1){
                outerMostY += button_height;
                elementsHeight += button_height;
            }else{
                outerMostY += button_height+button_spacingXY;
                elementsHeight += button_height+button_spacingXY;
            }
        }
    }
    outerMostY+=element_spacingY;
    QList<float> ret = {outerMostX,outerMostY,elementsHeight,buttons_width};

    return ret;
}

Scene* AbstractDialog::getScene(){
    return this->scene;
}
