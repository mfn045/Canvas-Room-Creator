#include "loadingbar.h"

LoadingBar::LoadingBar(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    MultiCanvasObject::PROPERTIES* bgProperties = new MultiCanvasObject::PROPERTIES();
    bgProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadingbar/background.svg";
    initFrames(bgProperties->filePath,bgProperties);
    setCurrentFrames(bgProperties);
    setFrame(0);
    setZValue(1001);

    bar = new MaskedMultiCanvasObject(this);
    MaskedMultiCanvasObject::PROPERTIES* barProperties = new MaskedMultiCanvasObject::PROPERTIES();
    barProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadingbar/bar.svg";
    bar->initFrames(barProperties->filePath,barProperties);
    bar->setCurrentFrames(barProperties);
    bar->setFrame(0);
    bar->setTransform(QTransform(1,0,0,1,23.5,7));
    bar->setZValue(1002);

    spinner = new MultiCanvasObject(this);
    spinner->setIndependentFromParent(true);
    MultiCanvasObject::PROPERTIES* spinnerProperties = new MultiCanvasObject::PROPERTIES();
    spinnerProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadingbar/spinner";
    spinner->initFrames(spinnerProperties->filePath,spinnerProperties);
    spinner->setCurrentFrames(spinnerProperties);
    spinner->setFrame(0);
    spinner->setTransform(QTransform(0.47180176,0,0,0.46832275,2,2));
    spinner->setHasAnimationLoop(true);
    spinner->setZValue(1003);
}


float LoadingBar::getPercent(){
    return this->percent;
}

void LoadingBar::setPercent(float percent){
    if(percent > 100){
        percent = 100;
    }else if(percent < 0){
        percent = 0;
    }
    this->percent = percent;
    QRectF rect = this->bar->boundingRect();
    float p1 = (100-percent)/100;
    float p2 = rect.width()*p1;
    float p3 = rect.width()-p2;
    this->bar->setMask(QRegion(rect.x(),rect.y(),p3,rect.height()));
    this->bar->update();
}


MaskedMultiCanvasObject* LoadingBar::getBar(){
    return this->bar;
}

MultiCanvasObject* LoadingBar::getSpinner(){
    return this->spinner;
}
