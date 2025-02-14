#include "oldplayerpage.h"

LoginScreen::OldPlayerPage::OldPlayerPage(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    LocalizationManager* lm = LocalizationManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.screens.loadingscreen.screen");
    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);
    setZValue(1000);

    LoginScreen::Buttons::OvalButton* login_other = new LoginScreen::Buttons::OvalButton(this);
    login_other->setText(lm->getText("login_screen.logon_different_penguin"));
    float lother_centerX = (boundingRect().width()-login_other->boundingRect().width())/2;
    float lother_Y = (boundingRect().height()-login_other->boundingRect().height())-15;
    login_other->setPos(QPointF(lother_centerX,lother_Y));
}

void LoginScreen::OldPlayerPage::addPlayer(QString name, PenguinPaper* paper){
    savedPenguins.insert(name,paper);
}

void LoginScreen::OldPlayerPage::drawSavedPlayers(){
    GridContainer* container = nullptr;
    int c = 0;
    int r = 0;

    if(savedPenguins.count() <= 2){
        container = new GridContainer(this);
        container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
        container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);
        container->setHorizontalSpacing(15);
        container->setVerticalSpacing(15);

        for(auto i = savedPenguins.begin(); i != savedPenguins.end(); i++){
            BackgroundContainer* bc = new BackgroundContainer(244,332);
            bc->init();
            LoginScreen::Buttons::PenguinSlotButton* slot = new LoginScreen::Buttons::PenguinSlotButton(bc,LoginScreen::Buttons::PenguinSlotButton::VERTICAL);
            i.value()->setParentItem(slot);
            float paper_centerX = (slot->boundingRect().width()-i.value()->boundingRect().width())/2;
            float paper_centerY = (slot->boundingRect().height()-i.value()->boundingRect().height())/2;
            i.value()->setPos(QPointF(paper_centerX,paper_centerY));

            TitleLabel* username = new TitleLabel(slot);
            username->setText(i.key());
            float username_centerX = (slot->boundingRect().width()-username->boundingRect().width())/2;
            float username_Y = slot->boundingRect().height()*0.9;
            username->setPos(QPointF(username_centerX,username_Y));

            float slot_centerX = (bc->getWidth()-slot->boundingRect().width())/2;
            float slot_centerY = (bc->getHeight()-slot->boundingRect().height())/2;
            slot->setPos(QPointF(slot_centerX,slot_centerY));
            container->addGridItem(bc,r,c);
            if(c == 1){
                r++;
                c = 0;
            }else{
                c++;
            }
        }
    } else if(savedPenguins.count() == 3){
        BackgroundContainer* bc = new BackgroundContainer(684,332);
        bc->setParentItem(this);
        bc->init();
        float bc_centerX = (boundingRect().width()-bc->getWidth())/2;
        float bc_centerY = (boundingRect().height()-bc->getHeight())/2;
        bc->setPos(QPointF(bc_centerX,bc_centerY));
        container = new GridContainer(bc);
        container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
        container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);
        container->setHorizontalSpacing(15);
        container->setVerticalSpacing(15);

        for(auto i = savedPenguins.begin(); i != savedPenguins.end(); i++){
            qDebug() << i.key();
            LoginScreen::Buttons::PenguinSlotButton* slot = new LoginScreen::Buttons::PenguinSlotButton(bc,LoginScreen::Buttons::PenguinSlotButton::VERTICAL);
            i.value()->setParentItem(slot);
            float paper_centerX = (slot->boundingRect().width()-i.value()->boundingRect().width())/2;
            float paper_centerY = (slot->boundingRect().height()-i.value()->boundingRect().height())/2;
            i.value()->setPos(QPointF(paper_centerX,paper_centerY));

            TitleLabel* username = new TitleLabel(slot);
            username->setText(i.key());
            float username_centerX = (slot->boundingRect().width()-username->boundingRect().width())/2;
            float username_Y = slot->boundingRect().height()*0.9;
            username->setPos(QPointF(username_centerX,username_Y));

            float slot_centerX = (bc->getWidth()-slot->boundingRect().width())/2;
            float slot_centerY = (bc->getHeight()-slot->boundingRect().height())/2;
            slot->setPos(QPointF(slot_centerX,slot_centerY));
            container->addGridItem(slot,r,c);
            if(c == 2){
                r++;
                c = 0;
            }else{
                c++;
            }
        }
    }else if(savedPenguins.count() == 4){
        container = new GridContainer(this);
        container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
        container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);
        container->setHorizontalSpacing(15);
        container->setVerticalSpacing(15);

        for(auto i = savedPenguins.begin(); i != savedPenguins.end(); i++){
            BackgroundContainer* bc = new BackgroundContainer(344,144);
            bc->init();
            LoginScreen::Buttons::PenguinSlotButton* slot = new LoginScreen::Buttons::PenguinSlotButton(bc,LoginScreen::Buttons::PenguinSlotButton::HORIZONTAL);
            i.value()->setParentItem(slot);
            float paper_X = -i.value()->boundingRect().width()*0.15;
            float paper_Y = i.value()->boundingRect().height()*0.1;
            i.value()->setPos(QPointF(paper_X,paper_Y));

            TitleLabel* username = new TitleLabel(slot);
            username->setText(i.key());
            float username_X = slot->boundingRect().width()*0.5;
            float username_centerY = ((slot->boundingRect().height())/2);
            username->setPos(QPointF(username_X,username_centerY));

            float slot_centerX = (bc->getWidth()-slot->boundingRect().width())/2;
            float slot_centerY = (bc->getHeight()-slot->boundingRect().height())/2;
            slot->setPos(QPointF(slot_centerX,slot_centerY));
            container->addGridItem(bc,r,c);
            if(c == 1){
                r++;
                c = 0;
            }else{
                c++;
            }
        }
    } else {
        BackgroundContainer* bc = new BackgroundContainer(656.1,364);
        bc->init();
        bc->setParentItem(this);
        float bc_centerX = (boundingRect().width()-bc->getWidth())/2;
        float bc_centerY = (boundingRect().height()-bc->getHeight())/2;
        bc->setPos(QPointF(bc_centerX,bc_centerY));
        container = new GridContainer(bc);
        container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
        container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);
        container->setHorizontalSpacing(15);
        container->setVerticalSpacing(15);

        for(auto i = savedPenguins.begin(); i != savedPenguins.end(); i++){
            LoginScreen::Buttons::PenguinSlotButton* slot = new LoginScreen::Buttons::PenguinSlotButton(bc,LoginScreen::Buttons::PenguinSlotButton::HORIZONTAL);
            i.value()->setParentItem(slot);
            float paper_X = -i.value()->boundingRect().width()*0.15;
            float paper_Y = i.value()->boundingRect().height()*0.1;
            i.value()->setPos(QPointF(paper_X,paper_Y));

            TitleLabel* username = new TitleLabel(slot);
            username->setText(i.key());
            float username_X = slot->boundingRect().width()*0.5;
            float username_centerY = (slot->boundingRect().height()-username->boundingRect().height())/2;
            username->setPos(QPointF(username_X,username_centerY));

            float slot_centerX = (bc->getWidth()-slot->boundingRect().width())/2;
            float slot_centerY = (bc->getHeight()-slot->boundingRect().height())/2;
            slot->setPos(QPointF(slot_centerX,slot_centerY));
            container->addGridItem(slot,r,c);
            if(c == 1){
                r++;
                c = 0;
            }else{
                c++;
            }
        }
    }
    if(container){
        container->updateLayout();
    }
}
