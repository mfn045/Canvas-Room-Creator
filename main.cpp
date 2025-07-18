#include <QApplication>
#include <QRect>
#include <QException>
#include <QFontDatabase>
#include "roomcanvas.h"
#include "LocalizationManager/localizationmanager.h"
#include "AssetsManager/assetsmanager.h"
#include "Game/game.h"
#include "Interface/interface.h"
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/CanvasObject/Atlas/atlascanvasobject.h"
#include "Interface/Common/TitleLabel/titlelabel.h"
#include "Interface/World/Penguin/Sprite/penguinsprite.h"
#include "Interface/Widgets/BackgroundContainer/backgroundcontainer.h"
#include "Interface/Widgets/Dialogs/YesNoDialog/yesnodialog.h"
#include "Interface/Widgets/Settings/settings.h"
#include "Interface/Screens/LoadingScreen/loading.h"
#include "Interface/Widgets/Buttons/CheckBoxButton/checkboxbutton.h"
#include "Interface/Screens/LoginScreen/Buttons/OvalButton/ovalbutton.h"
#include "Interface/Screens/LoginScreen/NewPlayerPage/newplayerpage.h"
#include "Interface/Screens/LoginScreen/OldPlayerPage/oldplayerpage.h"
#include "Interface/Screens/LoginScreen/ServerSelectionPage/serverselectionpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    RoomCanvas* w = new RoomCanvas();
    w->setWindowTitle("Clubpenguin Room Creator");
    w->setWindowIcon(QIcon(":/resources/Resources/logo.png"));
    w->show();

    LocalizationManager* lm = LocalizationManager::getInstance();
    lm->setLocale(LocalizationManager::LOCALE::EN);
    lm->loadLocaleFile();

    AssetsManager* am = AssetsManager::getInstance();
    am->loadAssetsFile();

    Game* game = Game::getInstance();

    PlayerFactory* factory = game->getPlayerFactory();

    Interface* interface = game->getInterface();
    interface->setScene(w->getScene());
/*
    Loading* loading = new Loading();
    interface->addToScene(loading);
    loading->addStep("Loading Items...");
    loading->addStep("Loading fonts...");
    loading->addStep("Loading HUD...");
    loading->addStep("Loading players...");
    loading->addStep("Loading player card...");
    loading->startLoading();*/

    interface->loadItems();
   // loading->incrementStep();
    interface->loadFonts();
   // loading->incrementStep();
    interface->loadHUD();
    //loading->incrementStep();

    Player* player1 = factory->createPlayer();
    player1->setUsername("Username1");
    player1->setBadge(PENGUIN::BADGE::MEMBER_2);
    player1->setID(1);
    factory->setActivePlayer(player1);
    PenguinSprite* player1_sprite = player1->getPenguinSprite();
    player1_sprite->initializeEvents(w->getScene());
    interface->addToScene(player1_sprite);
    QObject::connect(player1->getPenguinSprite(),&PenguinSprite::clickedPenguin, [interface,player1](){
        PlayerCard* pc = interface->getPlayerCard();
        if(pc && player1){
            if(pc->currentPlayer() != player1){
                pc->setPlayer(player1);
            }
            pc->show();
        }
    });
    player1->getOwnedItems().append(1);
    player1->getOwnedItems().append(2);
    player1->getOwnedItems().append(212);

    Player* player2 = factory->createPlayer();
    player2->setUsername("Username2");
    player2->setBadge(PENGUIN::BADGE::MEMBER_0);
    player2->setID(2);
    interface->addToScene(player2->getPenguinSprite());
    QObject::connect(player2->getPenguinSprite(),&PenguinSprite::clickedPenguin, [interface,player2](){
        PlayerCard* pc = interface->getPlayerCard();
        if(pc && player2){
            if(pc->currentPlayer() != player2){
                pc->setPlayer(player2);
            }
            pc->show();
        }
    });
    for(int i = 0; i < 500; i++){
        player2->getOwnedItems().append(i);
    }
    //loading->incrementStep();

    interface->loadPlayerCard();

    //LoginScreen::ServerSelectionPage* sp = new LoginScreen::ServerSelectionPage();
    //interface->addToScene(sp);
/*
    LoginScreen::OldPlayerPage* op = new LoginScreen::OldPlayerPage();

    PenguinPaper* player1Paper = new PenguinPaper();
    player1Paper->setColor(3);
    player1Paper->setHead(403);
    op->addPlayer("Enhanced",player1Paper);

    PenguinPaper* player2Paper = new PenguinPaper();
    player2Paper->setColor(5);
    player2Paper->setFace(106);
    op->addPlayer("Try AgainWfLF",player2Paper);

    /*PenguinPaper* player3Paper = new PenguinPaper();
    player3Paper->setColor(10);
    op->addPlayer("Aced",player3Paper);

    PenguinPaper* player4Paper = new PenguinPaper();
    player4Paper->setColor(14);
    op->addPlayer("Fourth",player4Paper);

    PenguinPaper* player5Paper = new PenguinPaper();
    player5Paper->setColor(13);
    op->addPlayer("tttt",player5Paper);

    op->drawSavedPlayers();

    interface->addToScene(op);*/

/*
    BackgroundContainer* bc = new BackgroundContainer();
    bc->setColor(BACKGROUNDCONTAINER::ORANGE);
    bc->setWidth(500);
    bc->setHeight(500);
    bc->init();
    interface->getScene()->addItem(bc);*/

    //LoginScreen_NewPlayer* loginScreen = new LoginScreen_NewPlayer();
    //interface->addToScene(loginScreen);

    //loading->incrementStep();
    //interface->getScene()->removeItem(loading);

    /*for(int i = 25; i < 50; i++){
        player1->getOwnedItems().append(i);
    }*/

    /*YesNoDialog* dialog = new YesNoDialog(w.getScene(),YesNoDialog::TYPE::ORANGE);
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->initDialog();
    w.getScene()->addItem(dialog);*/

    /*CanvasObject* rect = new MultiCanvasObject();
    MultiCanvasObject::PROPERTIES* properties = new MultiCanvasObject::PROPERTIES();
    properties->filePath ="C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/test/test.svg";
    rect->initFrames(properties->filePath,properties);
    rect->setCurrentFrames(properties);
    qDebug() << "RECT UPDATE :: " << rect->boundingRect() << rect->sceneBoundingRect();
    rect->setFrame(0);
    rect->setScale(0.5);
    qDebug() << "RECT UPDATE :: " << rect->boundingRect() << rect->sceneBoundingRect();
    rect->setPos(50,50);
    rect->setID(w.getScene()->getUniqueID());
    w.getScene()->addItem(rect);
    //w.updateLayers();
    w.update();

    GridContainer* container = new GridContainer(rect);
    container->setID(w.getScene()->getUniqueID());
    /*for(int r = 0; r < 2; r++){
        for(int c = 0; c < 2; c++){
            if(r == 2 && c == 2){
                container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::SMALL),r,c);
            }else{
                container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::SMALL),r,c);
            }
        }
    }
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,0);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,1);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,2);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,4);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),2,0);
    container->updateLayout();*/
    qDebug() << " ------------- TEST --------------- ";
    //qDebug() << obj1 << obj1->pos();
    //qDebug() << obj2 << obj2->pos();
    //qDebug() << obj3 << obj3->pos();
    /*AtlasCanvasObject* atlas = new AtlasCanvasObject();
    atlas->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas->setCurrentSprite(10);
    atlas->setFrame(0);
    atlas->setHasAnimationLoop(true);
    w.getScene()->addItem(atlas);*/


    /*AtlasCanvasObject* atlas2 = new AtlasCanvasObject();
    atlas2->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas2->setCurrentSprite(10);
    atlas2->setFrame(0);
    atlas2->setHasAnimationLoop(true);
    atlas2->setPos(QPointF(100,100));
    w.getScene()->addItem(atlas2);


    AtlasCanvasObject* atlas3 = new AtlasCanvasObject();
    atlas3->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas3->setCurrentSprite(10);
    atlas3->setFrame(0);
    atlas3->setHasAnimationLoop(true);
    atlas3->setPos(QPointF(200,200));
    w.getScene()->addItem(atlas3);
*/
    qDebug() << " -------------- END --------------- ";


    return a.exec();
}
