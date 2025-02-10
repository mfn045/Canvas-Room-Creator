#include "loadingbarworker.h"

LoadingBarWorker::LoadingBarWorker(int currentStep, int maxSteps, int currentPercent) : currentStep(currentStep), maxSteps(maxSteps), currentPercent(currentPercent) {
    setAutoDelete(true);
}

void LoadingBarWorker::incrementStep(){
    if(currentStep < maxSteps){
        currentStep++;
    }
}

void LoadingBarWorker::run(){
    while(currentPercent < 100){
        float divided = 100/maxSteps;
        if(currentPercent < (currentStep*divided)){
            currentPercent++;
            emit setBarPercent(currentPercent);
        }
        QThread::msleep(5);
    }
}
