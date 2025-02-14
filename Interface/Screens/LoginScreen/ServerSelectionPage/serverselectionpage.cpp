#include "serverselectionpage.h"

LoginScreen::ServerSelectionPage::ServerSelectionPage(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    LocalizationManager* lm = LocalizationManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.screens.loadingscreen.screen");
    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);
    setZValue(1000);

    int r = 0;
    int c = 0;

    TitleLabel* selectServer = new TitleLabel(this);
    selectServer->setText(lm->getText("login_screen.suggested_servers"));
    float selectServer_centerX = (boundingRect().width()-selectServer->boundingRect().width())/2;
    float selectServer_Y = 50;
    selectServer->setPos(QPointF(selectServer_centerX,selectServer_Y));

    r = 0;
    c = 0;
    GridContainer* serversContainer = new GridContainer(this);
    serversContainer->setVerticalSpacing(5);
    serversContainer->color = QColor(0,255,0,255);

    for(int i = 0; i < 5; i++){
        LoginScreen::Buttons::ServerButton* button = new LoginScreen::Buttons::ServerButton(this);
        GRIDCONTAINER::CELL_PROPERTIES* cell = serversContainer->addGridItem(button,r++,c);
    }

    serversContainer->updateLayout();
    serversContainer->addCallbackFunction([serversContainer, this](){
        if(serversContainer){
            serversContainer->setScale(1.6);
            float centerX = (boundingRect().width()-serversContainer->getWidth())/2;
            //float centerY = (boundingRect().height()-serversContainer->getHeight())/2;
            serversContainer->setPos(QPointF(centerX,80));
        }
    });

}
