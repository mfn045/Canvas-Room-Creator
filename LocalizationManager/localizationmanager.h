#ifndef LOCALIZATIONMANAGER_H
#define LOCALIZATIONMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class LocalizationManager
{
public:
    enum LOCALE {
        EN,
        PT,
        FR,
        ES,
        DE,
        RU
    };
    static LocalizationManager* getInstance();

    LOCALE getLocale();
    LOCALE setLocale(LOCALE locale);
    bool loadLocaleFile();

    QString getText(QString key);

    LocalizationManager& operator=(const LocalizationManager&) = delete;
    LocalizationManager& operator=(LocalizationManager&&) = delete;
private:
    LocalizationManager() = default;
    static LocalizationManager* instance;
    void recurse(QString key, QJsonObject& obj);
    LOCALE locale = LOCALE::EN;
    QHash<QString,QString> map;
};

#endif // LOCALIZATIONMANAGER_H
