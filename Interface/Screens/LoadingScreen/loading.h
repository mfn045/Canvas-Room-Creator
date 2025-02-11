#ifndef LOADING_H
#define LOADING_H

#include "loadingbar.h"
#include "ThreadPoolManager/LoadingBarWorker/loadingbarworker.h"
#include "ThreadPoolManager/threadpoolmanager.h"
#include "Interface/Common/TextLabel/textlabel.h"

class Loading : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit Loading(MultiCanvasObject* parent = nullptr);

    LoadingBar* getBar();

    void addStep(QString msg);
    void incrementStep();

    void startLoading();

private:
    LoadingBar* bar = nullptr;

    MultiCanvasObject* animation = nullptr;

    TextLabel* label = nullptr;

    QList<QString> steps;

    int currentStep = 1;

public slots:
    void setBarPercent(float percent);

signals:
    void incrementWorkerStep();

};

#endif // LOADING_H
