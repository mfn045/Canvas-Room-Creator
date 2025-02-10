#ifndef THREADPOOLMANAGER_H
#define THREADPOOLMANAGER_H

#include <QThreadPool>
#include "PenguinSpriteMoveWorker/penguinspritemoveworker.h"

class ThreadPoolManager : public QThreadPool
{
public:
    static ThreadPoolManager* getInstance();

    PenguinSpriteMoveWorker* getPSMW();
    void resetPSMW();

    ThreadPoolManager& operator=(const ThreadPoolManager&) = delete;
    ThreadPoolManager& operator=(ThreadPoolManager&&) = delete;

private:
    ThreadPoolManager() = default;

    static ThreadPoolManager* instance;

    PenguinSpriteMoveWorker* psmw = nullptr;
};

#endif // THREADPOOLMANAGER_H
