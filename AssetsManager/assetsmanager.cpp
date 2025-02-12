#include "assetsmanager.h"

bool AssetsManager::loadAssetsFile(){
    QString path = "assets/";
    LocalizationManager* lm = LocalizationManager::getInstance();
    LocalizationManager::LOCALE locale = lm->getLocale();
    if(locale == LocalizationManager::LOCALE::EN){
        path += "assets_en";
    } else if(locale == LocalizationManager::LOCALE::PT){
        path += "assets_pt";
    } else if(locale == LocalizationManager::LOCALE::FR){
        path += "assets_fr";
    } else if(locale == LocalizationManager::LOCALE::ES){
        path += "assets_es";
    } else if(locale == LocalizationManager::LOCALE::DE){
        path += "assets_de";
    } else if(locale == LocalizationManager::LOCALE::RU){
        path += "assets_ru";
    }
    path += ".json";
    QFile file(path);
    if(!file.exists()){
        qDebug() << "[Error] File '" << path << "' does not exist!";
        return false;
    }
    if(file.open(QFile::ReadOnly)){
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),&error);
        if(doc.isNull()){
            qDebug() << "[Error] Cannot parse json file '" << path << "'. Error Code: " << error.errorString();
            return false;
        }
        QJsonObject root = doc.object();
        QString key = "";
        recurse(key,root);
    }else{
        qDebug() << "[Error] Cannot read '" << path << "' file. Error Code: " << file.errorString();
        return false;
    }
    qDebug() << map;
    return true;
}

void AssetsManager::recurse(QString k, QJsonObject& obj){
    for(auto i = obj.begin(); i != obj.end(); i++){
        QString key = k;
        if(!key.isEmpty()){
            key += ".";
        }
        QString keyAddition = i.key();
        key+= keyAddition;
        QJsonValueRef valueRef = i.value();
        if(valueRef.isObject()){
            QJsonObject valueObj = valueRef.toObject();
            recurse(key, valueObj);
        } else if(valueRef.isString()){
            map.insert(key,valueRef.toString());
        }
    }
}

QString AssetsManager::getAssetPath(QString key){
    return this->map.value(key);
}

AssetsManager* AssetsManager::getInstance(){
    if(instance == nullptr){
        instance = new AssetsManager();
    }
    return instance;
}

AssetsManager* AssetsManager::instance = nullptr;
