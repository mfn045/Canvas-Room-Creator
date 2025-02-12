#include "dialoggrid.h"

DialogGrid::DialogGrid(Scene* parent, TYPE type) {
    if(parent != nullptr){
        this->scene = parent;
    }
    gridTransform = QTransform(1,0,0,1,0,0);
    setGridSize(43,43);
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

    AssetsManager* am = AssetsManager::getInstance();
    if(type == TYPE::BLUE){
        this->path_top_left = am->getAssetPath("interface.widgets.dialogs.grid.blue.top_left");
        this->path_top = am->getAssetPath("interface.widgets.dialogs.grid.blue.top");
        this->path_top_right = am->getAssetPath("interface.widgets.dialogs.grid.blue.top_right");
        this->path_bottom_left = am->getAssetPath("interface.widgets.dialogs.grid.blue.bottom_left");
        this->path_bottom = am->getAssetPath("interface.widgets.dialogs.grid.blue.bottom");
        this->path_bottom_right = am->getAssetPath("interface.widgets.dialogs.grid.blue.bottom_right");
        this->path_left = am->getAssetPath("interface.widgets.dialogs.grid.blue.left");
        this->path_center = am->getAssetPath("interface.widgets.dialogs.grid.blue.center");
        this->path_right = am->getAssetPath("interface.widgets.dialogs.grid.blue.right");
    }else if(type == TYPE::ORANGE){
        this->path_top_left = am->getAssetPath("interface.widgets.dialogs.grid.orange.top_left");
        this->path_top = am->getAssetPath("interface.widgets.dialogs.grid.orange.top");
        this->path_top_right = am->getAssetPath("interface.widgets.dialogs.grid.orange.top_right");
        this->path_bottom_left = am->getAssetPath("interface.widgets.dialogs.grid.orange.bottom_left");
        this->path_bottom = am->getAssetPath("interface.widgets.dialogs.grid.orange.bottom");
        this->path_bottom_right = am->getAssetPath("interface.widgets.dialogs.grid.orange.bottom_right");
        this->path_left = am->getAssetPath("interface.widgets.dialogs.grid.orange.left");
        this->path_center = am->getAssetPath("interface.widgets.dialogs.grid.orange.center");
        this->path_right = am->getAssetPath("interface.widgets.dialogs.grid.orange.right");
    }

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
                top_left = new MultiCanvasObject();
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
                top = new MultiCanvasObject();
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
                top_right = new MultiCanvasObject();
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
                left = new MultiCanvasObject();
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
                right = new MultiCanvasObject();
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
                bottom_left = new MultiCanvasObject();
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
                bottom = new MultiCanvasObject();
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
                bottom_right = new MultiCanvasObject();
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
                center = new MultiCanvasObject();
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
