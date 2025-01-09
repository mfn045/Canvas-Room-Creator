#include "yesnodialog.h"

YesNoDialog::YesNoDialog(Scene* parent, TYPE type) : AbstractDialog(parent,type) {
}

bool YesNoDialog::initDialog(){
    int row = 1;
    int col = 1;

    addButton("Yes");
    addButton("No");

    QList<float> measurements = approximateMeasurements();
    while(col*getGridSize() < measurements[0]){
        col++;
    }
    while(row*getGridSize() < measurements[1]){
        row++;
    }
    setRow(row);
    setCol(col);

    bool ret = init();

    setElementsPositions(measurements[2],measurements[3]);

    setDialogPosition();

    return ret;
}
