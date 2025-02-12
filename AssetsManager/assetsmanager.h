#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "LocalizationManager/localizationmanager.h"

class AssetsManager
{
public:
    static AssetsManager* getInstance();

    bool loadAssetsFile();

    QString getAssetPath(QString key);

    AssetsManager& operator=(const AssetsManager&) = delete;
    AssetsManager& operator=(AssetsManager&&) = delete;
private:
    AssetsManager() = default;
    static AssetsManager* instance;
    void recurse(QString key, QJsonObject& obj);
    QHash<QString,QString> map;
};

#endif // ASSETSMANAGER_H
