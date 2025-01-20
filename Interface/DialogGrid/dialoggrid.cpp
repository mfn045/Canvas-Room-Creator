#include "dialoggrid.h"

DialogGrid::DialogGrid(Scene* parent, TYPE type) {
    if(parent != nullptr){
        this->scene = parent;
    }
    gridTransform = QTransform(1,0,0,1,0,0);
    setGridSize(43.5,43.5);
    setType(type);

}


float DialogGrid::setWidth(float width){
    int colRequired = round(width/getGridSizeX());
    double scaleRequired = width/(getGridSizeX()*colRequired);
    qDebug() << " WIDTH HISSSAJDASKDJAS " << colRequired << width << getGridSizeX() << scaleRequired << getGridSizeX()*scaleRequired;
    setCol(colRequired);
    gridTransform.setMatrix(scaleRequired,gridTransform.m12(),gridTransform.m13(),
                            gridTransform.m21(),gridTransform.m22(),gridTransform.m23(),
                            gridTransform.m31(),gridTransform.m32(),gridTransform.m33());
    //setTransform(gridTransform);
    setGridSize(scaleRequired*getGridSizeX(),getGridSizeY());
    return width;
}

float DialogGrid::setHeight(float height){
    int rowRequired = round(height/getGridSizeY());
    double scaleRequired = height/(getGridSizeY()*rowRequired);
    setRow(rowRequired);
    gridTransform.setMatrix(gridTransform.m11(),gridTransform.m12(),gridTransform.m13(),
                            gridTransform.m21(),scaleRequired,gridTransform.m23(),
                            gridTransform.m31(),gridTransform.m32(),gridTransform.m33());
    //setTransform(gridTransform);
    setGridSize(getGridSizeX(),scaleRequired*getGridSizeY());
    return height;
}

/*float DialogGrid::getScale(){
    return this->scale;
}

float DialogGrid::setScale(float scale){
    this->scale = scale;
    setGridSize(43*scale);
    return this->scale;
}*/

float DialogGrid::getGridSizeX(){
    return this->gridSize_X;
}
float DialogGrid::getGridSizeY(){
    return this->gridSize_Y;
}

void DialogGrid::setGridSize(float gridSize_X, float gridSize_Y){
    this->gridSize_X = gridSize_X;
    this->gridSize_Y = gridSize_Y;
    return;
}


DialogGrid::TYPE DialogGrid::getType(){
    return this->type;
}

DialogGrid::TYPE DialogGrid::setType(TYPE type){
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

int DialogGrid::getRow(){
    return this->row;
}

int DialogGrid::setRow(int row){
    this->row = row;
    return this->row;
}

int DialogGrid::getCol(){
    return this->col;
}

int DialogGrid::setCol(int col){
    this->col = col;
    return this->col;
}

bool DialogGrid::init(){
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
                top_left->setTransform(gridTransform);
                top_left->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                qDebug() << "TOP LEFT SIZE " << top_left->transform() << top_left->sceneTransform() << top_left->sceneBoundingRect() << top_left->boundingRect();
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                top->setTransform(gridTransform);
                top->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                top_right->setTransform(gridTransform);
                top_right->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                left->setTransform(gridTransform);
                left->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                right->setTransform(gridTransform);
                right->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                bottom_left->setTransform(gridTransform);
                bottom_left->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                bottom->setTransform(gridTransform);
                bottom->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                bottom_right->setTransform(gridTransform);
                bottom_right->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
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
                center->setTransform(gridTransform);
                center->setPos(QPointF(gridSize_X*k,gridSize_Y*j));
                if(gridSize_X*k > farthest_x){
                    farthest_x = gridSize_X*k;
                }
                if(gridSize_Y*j > farthest_y){
                    farthest_y = gridSize_Y*j;
                }
            }
        }
    }
    update();
    return true;
}


QRectF DialogGrid::boundingRect() const {
    return QRect(pos().x(),pos().y(),getWidth(),getHeight());
}

float DialogGrid::getWidth() const{
    return gridSize_X*col;
}

float DialogGrid::getHeight() const{
    return gridSize_Y*row;
}
