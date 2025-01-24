#ifndef ITEMS_H
#define ITEMS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class Items
{
public:
    static Items* getInstance();
    int getType(int itemId);
    int getCost(int itemId);
    bool isBait(int itemId);
    bool isPatched(int itemId);
    bool exists(int itemId);

private:
    Items();
    QJsonObject object;
    static Items* items;
};

#endif // ITEMS_H
