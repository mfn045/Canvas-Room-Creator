#include "gridcontainer.h"

GridContainer::GridContainer(MultiCanvasObject* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
}

GridContainer::GridContainer(QRectF parentRect) {
    if(!parentRect.isNull()){
        this->parentRect = parentRect;
    }
}

bool GridContainer::locationOccupied(int row, int col){
    for(auto i = map.begin(); i != map.end(); i++){
        if(i.key()->col == col && i.key()->row == row){
            return true;
        }
    }
    return false;
}


float GridContainer::setMaxWidth(int column, float maxWidth){
    if(!(this->maxWidth.size() >= column)) return -1;
    this->maxWidth[column] = maxWidth;
    return this->maxWidth[column];
}

float GridContainer::getMaxWidth(int column){
    if(!(maxWidth.size() >= column)) return -1;
    return maxWidth[column];
}

float GridContainer::setMaxHeight(int row, float maxHeight){
    if(!(this->maxHeight.size() >= row)) return -1;
    this->maxHeight[row] = maxHeight;
    return this->maxHeight[row];
}

float GridContainer::getMaxHeight(int row){
    if(!(maxHeight.size() >= row)) return -1;
    return maxHeight[row];
}

void GridContainer::updateMaximums(){
    maxWidth.resize(lastColumn+1);
    maxHeight.resize(lastRow+1);
    for(auto i = map.begin(); i != map.end(); i++){
        QRectF itemBoundingRect = i.value()->boundingRect();//(i.value()->boundingRect()*i.value()->sceneTransform()).boundingRect();
        if(i.value()){
            if(i.key()->horizontalSpan != 0 && i.key()->horizontalSpan > 1){
                qDebug() << "Yep spanned horizontally";
                double horizontalWidth = itemBoundingRect.width()/i.key()->horizontalSpan;
                for(int c = i.key()->col; c <= i.key()->col+(i.key()->horizontalSpan-1); c++){
                    qDebug() << c << c+(i.key()->horizontalSpan-1);
                    if(maxWidth.size() > c)
                    {
                        if(maxWidth[c] < horizontalWidth){
                            maxWidth[c] = horizontalWidth;
                        }
                    }else{
                        maxWidth.resize(c+1);
                        maxWidth[c] = horizontalWidth;
                    }
                }
            }else{
                qDebug() << "Nope no horizontal span";
                if(maxWidth.size() > i.key()->col)
                {
                    if(maxWidth[i.key()->col] < itemBoundingRect.width()){
                        maxWidth[i.key()->col] = itemBoundingRect.width();
                    }
                }else{
                    maxWidth.resize(i.key()->col+1);
                    maxWidth[i.key()->col] = itemBoundingRect.width();
                }
            }
            if(i.key()->verticalSpan != 0 && i.key()->verticalSpan > 1){
                qDebug() << "Yep spanned vertically";
                double verticalHeight = itemBoundingRect.height()/i.key()->verticalSpan;
                for(int r = i.key()->row; r <= i.key()->row+(i.key()->verticalSpan-1); r++){
                    qDebug() << r << r+(i.key()->verticalSpan-1);
                    if(maxHeight.size() > r)
                    {
                        if(maxHeight[r] < verticalHeight){
                            maxHeight[r] = verticalHeight;
                        }
                    }else{
                        maxHeight.resize(r+1);
                        maxHeight[r] = verticalHeight;
                    }
                }
            }else{
                qDebug() << "Nope spanned vertically";
                if(maxHeight.size() > i.key()->row)
                {
                    if(maxHeight[i.key()->row] < itemBoundingRect.height()){
                        maxHeight[i.key()->row] = itemBoundingRect.height();
                    }
                }else{
                    maxHeight.resize(i.key()->row+1);
                    maxHeight[i.key()->row] = itemBoundingRect.height();
                }
            }
        }
    }
}


GridContainer::CELL_PROPERTIES* GridContainer::getCellProperties(MultiCanvasObject* object){
    return map.key(object);
}

GridContainer::CELL_PROPERTIES* GridContainer::getCellProperties(int row, int column){
    for(auto i = map.begin(); i != map.end(); i++){
        if(i.key()->col == column && i.key()->row == row){
            return i.key();
        }
    }
    return nullptr;
}

GridContainer::CELL_PROPERTIES* GridContainer::addGridItem(QGraphicsItem* gridItem, int row, int col, int horizontalSpan, int verticalSpan){
    if(locationOccupied(row,col)) return nullptr;
    qDebug() << "Added Item";
    CELL_PROPERTIES* cellP = new CELL_PROPERTIES();
    cellP->row = row;
    cellP->col = col;
    cellP->horizontalSpan = horizontalSpan;
    cellP->verticalSpan = verticalSpan;
    map.insert(cellP,gridItem);
    gridItem->setParentItem(this);

    if(lastRow < row+(verticalSpan-1)){
        lastRow = row+(verticalSpan-1);
    }
    if(lastColumn < col+(horizontalSpan-1)){
        lastColumn = col+(horizontalSpan-1);
    }
    qDebug() << "Updated last variables : " << lastRow << lastColumn;
    updateMaximums();
    return cellP;
}

QRectF GridContainer::boundingRect() const {
    return QRect(0,0,getWidth(),getHeight());
}

GridContainer::CELL_PROPERTIES* GridContainer::addGridItem(MultiCanvasObject* gridItem, int row, int col, int horizontalSpan, int verticalSpan){
    if(locationOccupied(row,col)) return nullptr;
    qDebug() << "Added Item";
    CELL_PROPERTIES* cellP = new CELL_PROPERTIES();
    cellP->row = row;
    cellP->col = col;
    cellP->horizontalSpan = horizontalSpan;
    cellP->verticalSpan = verticalSpan;
    map.insert(cellP,gridItem);
    gridItem->setParentItem(this);

    if(lastRow < row){
        lastRow = row;
    }
    if(lastColumn < col){
        lastColumn = col;
    }
    qDebug() << "Updated last variables : " << lastRow << lastColumn;
    updateMaximums();
    return cellP;
}

int GridContainer::setHorizontalSpacing(int horizontalSpacing){
    this->horizontalSpacing = horizontalSpacing;
    return this->horizontalSpacing;
}

int GridContainer::getHorizontalSpacing(){
    return this->horizontalSpacing;
}

int GridContainer::setVerticalSpacing(int verticalSpacing){
    this->verticalSpacing = verticalSpacing;
    return this->verticalSpacing;
}

int GridContainer::getVerticalSpacing(){
    return this->verticalSpacing;
}

void GridContainer::updateLayout(){
    qDebug() << maxWidth;
    qDebug() << maxHeight;
    int gridMaxWidth = 0;
    int gridMaxHeight = 0;
    if(parentItem()){
        QRectF parentBoundingRect = parentItem()->boundingRect();
        gridMaxWidth = parentBoundingRect.width();
        gridMaxHeight = parentBoundingRect.height();
        qDebug() << "Parent rect bounding width : " << gridMaxWidth;
        qDebug() << "Parent rect bounding height : " << gridMaxWidth;
    }else if(!parentRect.isNull()){
        gridMaxWidth = parentRect.width();
        gridMaxHeight = parentRect.height();
        qDebug() << "Parent rect bounding width : " << gridMaxWidth;
        qDebug() << "Parent rect bounding height : " << gridMaxWidth;
    }
    int gridXSoFar = 0;
    int gridYSoFar = 0;

    int occupiedRows = 0;
    int occupiedColumns = 0;

    int emptyRows = 0;
    int emptyColumns = 0;

    for(int width : maxWidth){
        gridXSoFar += width;
        if(width > 0){
            occupiedColumns++;
        }else{
            emptyColumns++;
        }
    }
    for(int height : maxHeight){
        gridYSoFar += height;
        if(height > 0){
            occupiedRows++;
        }else{
            emptyRows++;
        }
    }

    qDebug() << "grid width used: " << gridXSoFar;
    qDebug() << "grid height used: " << gridYSoFar;

    int gridWidthLeft = gridMaxWidth - gridXSoFar;
    int gridHeightLeft = gridMaxHeight - gridYSoFar;
    qDebug() << "grid width left: " << gridWidthLeft;
    qDebug() << "grid height left: " << gridHeightLeft;

    qDebug() << "Measured occupied rows: " << occupiedRows << ", therefore empty rows: " << emptyRows;
    qDebug() << "Measured occupied columns: " << occupiedColumns << ", therefore empty rows: " << emptyColumns;

    int emptyCellWidth = 0;
    if(emptyColumns > 0){
        emptyCellWidth = (gridWidthLeft/emptyColumns)-(((lastColumn*2)*horizontalSpacing)/emptyColumns);
    }
    int emptyCellHeight = 0;
    if(emptyRows > 0){
        emptyCellHeight = (gridHeightLeft/emptyRows)-(((lastRow*2)*verticalSpacing)/emptyRows);
    }

    qDebug() << "Empty Cell Width: " << emptyCellWidth;
    qDebug() << "Empty Cell Height: " << emptyCellHeight;

    int x = leftMargin;
    int y = topMargin;
    qDebug() << maxWidth;
    qDebug() << maxHeight;
    for(int r = 0; r <= lastRow; r++){
        for(int c = 0; c <= lastColumn; c++){
            qDebug() << r << c;
            bool foundGridItem = false;
            for(auto i = map.begin(); i != map.end(); i++){
                if(i.key()->col == c && i.key()->row == r){
                    int offsetY = 0;
                    int offsetX = 0;
                    QRectF itemBoundingRect = (i.value()->boundingRect()*i.value()->sceneTransform()).boundingRect();
                    if(maxHeight[r] != 0 && maxHeight[r] != itemBoundingRect.height() || i.key()->verticalSpan != 1){ // TO FIX
                        qDebug() << "Its not the height of the cell..." << (maxHeight[r] != 0) << (maxHeight[r] != itemBoundingRect.height()) << (i.key()->verticalSpan != 1);
                        if(i.key()->verticalAlignment == VerticalAlignment::CENTER){
                            if(i.key()->verticalSpan != 0 && i.key()->verticalSpan > 1){
                                double verticalHeight = 0;
                                for(int f = i.key()->row; f <= i.key()->row+(i.key()->verticalSpan-1); f++){
                                    if(f == i.key()->row+(i.key()->verticalSpan-1)){
                                        verticalHeight += maxHeight[f];
                                    }else{
                                        verticalHeight += maxHeight[f] + verticalSpacing;
                                    }
                                }
                                offsetY = (verticalHeight-itemBoundingRect.height())/2;
                                y += offsetY;
                            }else{
                                offsetY = (maxHeight[r]-itemBoundingRect.height())/2;
                                y += offsetY;
                            }
                        } if(i.key()->verticalAlignment == VerticalAlignment::BOTTOM){
                            if(i.key()->verticalSpan != 0 && i.key()->verticalSpan > 1){
                                double verticalHeight = 0;
                                for(int f = i.key()->row; f <= i.key()->row+(i.key()->verticalSpan-1); f++){
                                    if(f == i.key()->row+(i.key()->verticalSpan-1)){
                                        verticalHeight += maxHeight[f];
                                    }else{
                                        verticalHeight += maxHeight[f] + verticalSpacing;
                                    }
                                }
                                offsetY = verticalHeight-itemBoundingRect.height();
                                y += offsetY;
                            }else{
                                offsetY = maxHeight[r]-itemBoundingRect.height();
                                y += offsetY;
                            }
                        }
                    }
                    qDebug() << maxWidth[c] << itemBoundingRect.width();
                    if(maxWidth[c] != 0 && maxWidth[c] != itemBoundingRect.width() || i.key()->horizontalSpan != 1){
                        qDebug() << "Its not the width of the cell...";
                        if(i.key()->horizontalAlignment == HorizontalAlignment::CENTER){
                            if(i.key()->horizontalSpan != 0 && i.key()->horizontalSpan > 1){
                                qDebug() << "FOUND A HORIZONTAL SPAN!!!!";
                                double horizontalWidth = 0;
                                for(int f = i.key()->col; f <= i.key()->col+(i.key()->horizontalSpan-1); f++){
                                    qDebug() << f << i.key()->col+(i.key()->horizontalSpan-1) << horizontalWidth;
                                    if(f == i.key()->col+(i.key()->horizontalSpan-1)){
                                        horizontalWidth += maxWidth[f];
                                    }else{
                                        horizontalWidth += maxWidth[f] + horizontalSpacing;
                                    }
                                }
                                offsetX = (horizontalWidth-itemBoundingRect.width())/2;
                                x += offsetX;
                            }else{
                                qDebug() << "NO HORIZONTAL SPAN!!!!";
                                offsetX = (maxWidth[c]-itemBoundingRect.width())/2;
                                x += offsetX;
                            }
                        } if(i.key()->horizontalAlignment == HorizontalAlignment::RIGHT){
                            if(i.key()->horizontalSpan != 0 && i.key()->horizontalSpan > 1){
                                double horizontalWidth = 0;
                                for(int f = i.key()->col; f <= i.key()->col+(i.key()->horizontalSpan-1); f++){
                                    qDebug() << f << i.key()->col+(i.key()->horizontalSpan-1) << horizontalWidth;
                                    if(f == i.key()->col+(i.key()->horizontalSpan-1)){
                                        horizontalWidth += maxWidth[f];
                                    }else{
                                        horizontalWidth += maxWidth[f] + horizontalSpacing;
                                    }
                                }
                                offsetX = horizontalWidth-itemBoundingRect.width();
                                x += offsetX;
                            }else{
                                offsetX = maxWidth[c]-itemBoundingRect.width();
                                x += offsetX;
                            }
                        }
                    }
                    i.value()->setPos(QPointF(x,y));
                    x -= offsetX;
                    y -= offsetY;
                    if(maxWidth[c] != 0){
                        qDebug() << "INCREASED X BASED ON MAX WIDTH";
                        x += maxWidth[c] + horizontalSpacing;
                    } else {
                        qDebug() << "INCREASED X BASED ON items WIDTH";
                        x += itemBoundingRect.width() + horizontalSpacing;
                    }
                    if(c == lastColumn){
                        qDebug() << "REACHED LAST COLUMN";
                        if(maxHeight[r] != 0){
                            qDebug() << "INCREASED Y BASED ON MAX HEIGHT";
                            y += maxHeight[r] + verticalSpacing;
                        }else{
                            qDebug() << "INCREASED Y BASED ON items height";
                            y += itemBoundingRect.width() + verticalSpacing;
                        }
                    }
                    qDebug() << "found item";
                    foundGridItem = true;
                }
            }
            if(!foundGridItem){
                qDebug() << "didnt find item";
                if(maxWidth[c] != 0){
                    qDebug() << "INCREASED X BASED ON MAX WIDTH";
                    x += maxWidth[c] + horizontalSpacing;
                }else{
                    qDebug() << "INCREASED X BASED ON items WIDTH";
                    x += emptyCellWidth + horizontalSpacing;
                }
                if(c == lastColumn){
                    if(maxHeight[r] != 0){
                        qDebug() << "INCREASED Y BASED ON MAX HEIGHT";
                        y += maxHeight[r] + verticalSpacing;
                    }else{
                        qDebug() << "INCREASED Y BASED ON items height";
                        y += emptyCellHeight + verticalSpacing;
                    }
                }
            }
            qDebug() << x << y;
        }
        x = leftMargin;
    }
    int posX = 0;
    int posY = 0;
    if(verticalAlignment == VerticalAlignment::CENTER){
        if(parentItem()){
            posY = (parentItem()->sceneBoundingRect().height()-getHeight())/2;
        }else if(!parentRect.isNull()){
            posY = (parentRect.height()-getHeight())/2;
        }
    }else if(verticalAlignment == VerticalAlignment::BOTTOM){
        if(parentItem()){
            posY = (parentItem()->sceneBoundingRect().height()-getHeight());
        }else if(!parentRect.isNull()){
            posY = (parentRect.height()-getHeight());
        }
    } else if(verticalAlignment == VerticalAlignment::TOP){
        posY = topMargin;
    }
    if(horizontalAlignment == HorizontalAlignment::CENTER){
        if(parentItem()){
            posX = (parentItem()->sceneBoundingRect().width()-getWidth())/2;
            qDebug() << "CENTER HORIZONTAL ALIGNMENT : " << parentItem()->sceneBoundingRect().width() << parentItem()->boundingRect().width() << getWidth() << posX;
        }else if(!parentRect.isNull()){
            posX = (parentRect.width()-getWidth())/2;
        }
    }else if(horizontalAlignment == HorizontalAlignment::RIGHT){
        if(parentItem()){
            posX = (parentItem()->sceneBoundingRect().width()-getWidth());
        }else if(!parentRect.isNull()){
            posX = (parentRect.width()-getWidth());
        }
    } else if(horizontalAlignment == HorizontalAlignment::LEFT){
        posX = leftMargin;
    }
    qDebug() << "FINAL POSITION :: " << pos();
    setPos(QPointF(posX,posY));
    qDebug() << "FINAL POSITION :: " << pos();
}

GridContainer::HorizontalAlignment GridContainer::setHorizontalAlignment(HorizontalAlignment hAlignment){
    this->horizontalAlignment = hAlignment;
    return this->horizontalAlignment;
}

GridContainer::HorizontalAlignment GridContainer::getHorizontalAlignment(){
    return this->horizontalAlignment;
}

GridContainer::VerticalAlignment GridContainer::setVerticalAlignment(VerticalAlignment vAlignment){
    this->verticalAlignment=vAlignment;
    return this->verticalAlignment;
}

GridContainer::VerticalAlignment GridContainer::getVerticalAlignment(){
    return this->verticalAlignment;
}

void GridContainer::setMargins(float top, float right, float bottom, float left){
    this->topMargin = top;
    this->rightMargin = right;
    this->bottomMargin = bottom;
    this->leftMargin = left;
}
float GridContainer::setTopMargin(float top){
    this->topMargin = top;
    return this->topMargin;
}
float GridContainer::getTopMargin(){
    return this->topMargin;
}
float GridContainer::setRightMargin(float right){
    this->rightMargin = right;
    return this->rightMargin;
}
float GridContainer::getRightMargin(){
    return this->rightMargin;
}
float GridContainer::setBottomMargin(float bottom){
    this->bottomMargin = bottom;
    return this->bottomMargin;
}
float GridContainer::getBottomMargin(){
    return this->bottomMargin;
}
float GridContainer::setLeftMargin(float left){
    this->leftMargin = left;
    return this->leftMargin;
}
float GridContainer::getLeftMargin(){
    return this->leftMargin;
}

float GridContainer::getWidth() const{
    float width = 0;
    if(leftMargin != 0){
        width+=leftMargin;
    }
    for(float w : maxWidth){
        width += w;
    }
    if(maxWidth.size() > 1){
        width += horizontalSpacing*(maxWidth.size()-1);
    }
    if(rightMargin != 0){
        width+=rightMargin;
    }
    return width;
}

float GridContainer::getHeight() const{
    float height = 0;
    if(topMargin != 0){
        height+=topMargin;
    }
    for(float h : maxHeight){
        height += h;
    }
    if(maxHeight.size() > 1){
        height += verticalSpacing*(maxHeight.size()-1);
    }
    if(bottomMargin != 0){
        height+=bottomMargin;
    }
    return height;
}
