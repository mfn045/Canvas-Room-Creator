#include "loading.h"

Loading::Loading(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadingbar/screen/screen.svg";
    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);
    setZValue(1000);

    bar = new LoadingBar(this);
    float bar_centerX = (boundingRect().width()-bar->boundingRect().width())/2;
    bar->setPos(QPointF(bar_centerX,boundingRect().height()*0.6));
    bar->setPercent(0);

    animation = new MultiCanvasObject(this);
    PROPERTIES* animationProperties = new PROPERTIES();
    srand(time(0));
    int r = (rand() % 3)+1;
    if(r == 1){
        animationProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadinganimation/cartsurfer";
    } else if(r == 2){
        animationProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadinganimation/pizzatoss";
    } else if(r == 3){
        animationProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/loadingscreen/loadinganimation/snowshovel";
    }
    animation->initFrames(animationProperties->filePath,animationProperties);
    animation->setCurrentFrames(animationProperties);
    animation->setFrame(0);
    animation->setHasAnimationLoop(true);
    float animation_centerX = (boundingRect().width()-animation->boundingRect().width())/2;
    float animation_centerY = (boundingRect().height()*0.58)-animation->boundingRect().height();
    animation->setPos(QPointF(animation_centerX,animation_centerY));

    label = new TextLabel(this);
    QFont font = label->getInput()->font();
    font.setFamily("Arial");
    font.setPointSizeF(16);
    label->getInput()->setStyleSheet("background-color:transparent; color:white;");
    label->getInput()->setFont(font);
    label->setText("");

    float label_centerX = (boundingRect().width()-label->boundingRect().width())/2;
    float label_centerY = bar->pos().y()+bar->boundingRect().height()+5;
    label->setPos(QPointF(label_centerX,label_centerY));
}

void Loading::addStep(QString msg){
    steps.append(msg);
}

void Loading::incrementStep(){
    emit incrementWorkerStep();
    if(currentStep < steps.count()){
        currentStep++;
        QFont font = label->getInput()->font();
        font.setFamily("Arial");
        font.setPointSizeF(16);
        label->getInput()->setWordWrap(true);
        label->getInput()->setStyleSheet("background-color:transparent; color:white;");
        label->getInput()->setFont(font);
        label->setText(steps.at(currentStep-1));

        float label_centerX = (boundingRect().width()-label->boundingRect().width())/2;
        float label_centerY = bar->pos().y()+bar->boundingRect().height()+5;
        label->setPos(QPointF(label_centerX,label_centerY));
    }
}

void Loading::startLoading(){
    setBarPercent(0);
    ThreadPoolManager* tpm = ThreadPoolManager::getInstance();
    LoadingBarWorker* loadingWorker = new LoadingBarWorker(currentStep, steps.count(), 0);
    connect(this,&Loading::incrementWorkerStep,loadingWorker,&LoadingBarWorker::incrementStep);
    connect(loadingWorker,&LoadingBarWorker::setBarPercent,this,&Loading::setBarPercent);
    tpm->start(loadingWorker);
}

LoadingBar* Loading::getBar(){
    return this->bar;
}

void Loading::setBarPercent(float percent){
    bar->setPercent(percent);
}
