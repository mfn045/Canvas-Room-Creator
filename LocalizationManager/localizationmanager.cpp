#include "localizationmanager.h"

LocalizationManager::LOCALE LocalizationManager::getLocale(){
    return this->locale;
}

LocalizationManager::LOCALE LocalizationManager::setLocale(LOCALE locale){
    this->locale = locale;
    return this->locale;
}

bool LocalizationManager::loadLocaleFile(){
    QString path = "locales/";
    if(locale == EN){
        path += "locale_en";
    } else if(locale == PT){
        path += "locale_pt";
    } else if(locale == FR){
        path += "locale_fr";
    } else if(locale == ES){
        path += "locale_es";
    } else if(locale == DE){
        path += "locale_de";
    } else if(locale == RU){
        path += "locale_ru";
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

void LocalizationManager::recurse(QString k, QJsonObject& obj){
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

QString LocalizationManager::getText(QString key){
    return this->map.value(key);
}

LocalizationManager* LocalizationManager::getInstance(){
    if(instance == nullptr){
        instance = new LocalizationManager();
    }
    return instance;
}

LocalizationManager* LocalizationManager::instance = nullptr;
