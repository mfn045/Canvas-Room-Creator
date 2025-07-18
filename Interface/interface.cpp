#include "interface.h"

Interface::Interface(){}


Interface* createInterface() {
    return new Interface();
}

Scene* Interface::getScene(){
    return this->scene;
}

Scene* Interface::setScene(Scene* scene){
    this->scene = scene;
    return this->scene;
}


bool Interface::loadItems(){
    Items* items = Items::getInstance();
    items->getCost(-1);
    return true;
}

bool Interface::loadFonts(){
    int id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Burbank Small Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Sans Serif.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Arial Narrow Bold.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;
    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Arial.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Burbank Small Bold.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/Burbank Small Medium.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/CCComicrazyRegular.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;

    id = QFontDatabase::addApplicationFont(":/resources/Font/latest/CCComicrazyItalic.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << id << family;
    return true;
}

bool Interface::addToScene(AbstractCanvasObject* obj){
    if(!scene) return false;
    scene->addItem(obj);
    return true;
}

bool Interface::loadPlayerCard(){
    if(playercard != nullptr) return false;
    playercard = new PlayerCard(scene);
    playercard->hide();
    playercard->setID(scene->getUniqueID());
    scene->addItem(playercard);
    return true;
}

PlayerCard* Interface::getPlayerCard(){
    return playercard;
}

bool Interface::loadHUD(){
    if(!scene) return false;
    ToolBar* bar = new ToolBar(scene);
    // w.getItems().append(bar);
    bar->setID(scene->getUniqueID());
    scene->addItem(bar);
    //w.updateLayers();
    //w.update();

    ChatHistory* chistory = new ChatHistory(scene);
    chistory->setID(scene->getUniqueID());
    scene->addItem(chistory);
    //w.updateLayers();
    //w.update();
    GridContainer* container = new GridContainer(scene->sceneRect());
    //container->setHorizontalAlignment(GridContainer::HorizontalAlignment::CENTER);
    //container->setVerticalAlignment(GridContainer::VerticalAlignment::CENTER);
    container->setHorizontalSpacing(15);
    container->setVerticalSpacing(15);
    qDebug() << scene->sceneRect();
    container->setID(scene->getUniqueID());
    scene->addItem(container);

    News* news = new News();
    container->addGridItem(news,0,0);
    //news->setPos(QPointF(35,25));
    //news->setID(scene->getUniqueID());
    //scene->addItem(news);
    //w.updateLayers();
    //w.update();

    Mail* mail = new Mail();
    container->addGridItem(mail,0,1);
    //mail->setPos(QPointF(35+news->boundingRect().width(),25));
    //w.getItems().append(mail);
    //mail->setID(scene->getUniqueID());
    //scene->addItem(mail);
    //w.updateLayers();
    //w.update();

    Friend_Requests* friend_requests = new Friend_Requests();
    container->addGridItem(friend_requests,0,2);
    //friend_requests->setPos(QPointF(35+news->boundingRect().width()+mail->boundingRect().width()+10,25));
    //w.getItems().append(friend_requests);
    //friend_requests->setID(scene->getUniqueID());
    //scene->addItem(friend_requests);
    //w.updateLayers();
    //w.update();


    Moderator* mod = new Moderator();
    container->addGridItem(mod,0,4);

    Map* map = new Map();
    container->addGridItem(map,2,0);

    /*
    Map* map3 = new Map();
    container->addGridItem(map3,0,5);*/
    //map->setPos(QPointF(35,scene->sceneRect().height()-map->boundingRect().height()-25));
    //w.getItems().append(map);
    //map->setID(scene->getUniqueID());
    //scene->addItem(map);
    //w.updateLayers();
    //w.update();

    /*bar->connect(bar->getSendChatButton(),&BlueCircleButton::clicked,[&](){
        if(penguin != nullptr && bar->getChatInput() != nullptr){
            QString currentText = bar->getChatInput()->getCurrentText();
            penguin->sendChatBubble(currentText);
            bar->getChatInput()->clearTextBox();
        }
    });*/
    container->updateLayout();
    return true;
}
