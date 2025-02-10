#include "threadpoolmanager.h"

ThreadPoolManager* ThreadPoolManager::getInstance(){
    if(instance == nullptr){
        instance = new ThreadPoolManager();
        instance->setMaxThreadCount(4);
    }
    return instance;
}


PenguinSpriteMoveWorker* ThreadPoolManager::getPSMW(){
    if(this->psmw == nullptr){
        this->psmw = new PenguinSpriteMoveWorker();
    }
    return this->psmw;
}


void ThreadPoolManager::resetPSMW(){
    if(this->psmw != nullptr){
        this->psmw = nullptr;
    }
}

ThreadPoolManager* ThreadPoolManager::instance = nullptr;
