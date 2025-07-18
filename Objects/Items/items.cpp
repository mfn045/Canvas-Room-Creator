#include "items.h"

Items::Items() {
    QFile file("://Resources/items.json");
    if(!file.exists())
        return;
    if(!file.open(QFile::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    object = doc.object();
    file.close();
}

Items* Items::getInstance(){
    if(items == nullptr){
        items = new Items();
    }
    return items;
}

bool Items::exists(int itemId){
    QJsonValue val = object.value(QString::number(itemId));
    return !val.isUndefined();
}

int Items::getType(int itemId){
    QJsonValue val = object.value(QString::number(itemId));
    if(val.isObject()){
        QJsonObject item = val.toObject();
        return item.value("type").toInt();
    }
    return -1;
}
int Items::getCost(int itemId){
    QJsonValue val = object.value(QString::number(itemId));
    if(val.isObject()){
        QJsonObject item = val.toObject();
        return item.value("cost").toInt();
    }
    return -1;
}

bool Items::isBait(int itemId){
    QJsonValue val = object.value(QString::number(itemId));
    if(val.isObject()){
        QJsonObject item = val.toObject();
        return item.value("bait").toBool();
    }
    return false;
}
bool Items::isPatched(int itemId){
    QJsonValue val = object.value(QString::number(itemId));
    if(val.isObject()){
        QJsonObject item = val.toObject();
        return item.value("patched").toBool();
    }
    return false;
}

Items* Items::items = nullptr;
