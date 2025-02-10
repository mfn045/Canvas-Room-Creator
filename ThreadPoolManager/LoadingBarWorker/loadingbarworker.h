#ifndef LOADINGBARWORKER_H
#define LOADINGBARWORKER_H

#include <QObject>
#include <QThread>
#include <QRunnable>

class LoadingBarWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit LoadingBarWorker(int currentStep, int maxSteps, int currentPercent);

private:
    float currentPercent = 0;
    int maxSteps = 1;
    int currentStep = 1;

public slots:
    void incrementStep();
    void run();

signals:
    void setBarPercent(float percent);
};

#endif // LOADINGBARWORKER_H
