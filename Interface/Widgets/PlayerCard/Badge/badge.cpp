#include "badge.h"

Badge::Badge(MultiCanvasObject* parent, PENGUIN::BADGE badgeType) {
    clearBadge();
}

Badge::~Badge(){
    clearBadge();
}

void Badge::setBadge(PENGUIN::BADGE badgeType){
    clearBadge();
    AssetsManager* am = AssetsManager::getInstance();
    if(badgeType == PENGUIN::BADGE::MEMBER_0
        || badgeType == PENGUIN::BADGE::MEMBER_1
        || badgeType == PENGUIN::BADGE::MEMBER_2
        || badgeType == PENGUIN::BADGE::MEMBER_3
        || badgeType == PENGUIN::BADGE::MEMBER_4){
        resetTransform();
        backgroundProperties = new PROPERTIES();
        backgroundProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.background");
        initFrames(backgroundProperties->filePath,backgroundProperties);
        setCurrentFrames(backgroundProperties);
        setFrame(0);

        flashy = new MaskedMultiCanvasObject(this);
        flashy->setHasAnimationLoop(true);
        flashy->setMask(am->getAssetPath("interface.widgets.playercard.badge.member.flashy_mask"));
        flashy->getRegion().translate(QPoint(323,381));
        PROPERTIES* flashyProperties = new PROPERTIES();
        flashyProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.flashy");
        flashy->initFrames(flashyProperties->filePath,flashyProperties);
        flashy->setCurrentFrames(flashyProperties);
        flashy->setFrame(0);
        flashy->setScale(0.215);
        flashy->setZValue(0);

        float flash_centerX = (boundingRect().width()-(flashy->boundingRect().width()*0.215))/2;
        int flash_centerY = -(flashy->boundingRect().height()*0.215)+(1.5*boundingRect().height());
        qDebug() << "TEST FLASHING " << boundingRect().width() << flashy->boundingRect().width() << boundingRect() << flash_centerX << flash_centerY;
        flashy->setPos(QPointF(flash_centerX,flash_centerY));

        star = new MultiCanvasObject(this);
        PROPERTIES* starProperties = new PROPERTIES();
        starProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.star");
        star->initFrames(starProperties->filePath,starProperties);
        star->setCurrentFrames(starProperties);
        star->setFrame(0);
        star->setZValue(1);
        float star_centerX = (boundingRect().width()-star->boundingRect().width())/2;
        star->setPos(QPointF(star_centerX,10));

        float ribbon_offset = 50;

        ribbon_front = new MultiCanvasObject(this);
        PROPERTIES* rfProperties = new PROPERTIES();
        rfProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.ribbon_front");
        ribbon_front->initFrames(rfProperties->filePath,rfProperties);
        ribbon_front->setCurrentFrames(rfProperties);
        ribbon_front->setFrame(0);
        ribbon_front->setZValue(3);
        float rf_centerX = (boundingRect().width()-ribbon_front->boundingRect().width())/2;
        ribbon_front->setPos(QPointF(rf_centerX,ribbon_offset));

        ribbon_back = new MultiCanvasObject(this);
        ribbon_back->setFlag(QGraphicsSvgItem::GraphicsItemFlag::ItemStacksBehindParent);
        PROPERTIES* rbProperties = new PROPERTIES();
        rbProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.ribbon_back");
        ribbon_back->initFrames(rbProperties->filePath,rbProperties);
        ribbon_back->setCurrentFrames(rbProperties);
        ribbon_back->setFrame(0);
        float rb_centerX = (boundingRect().width()-ribbon_back->boundingRect().width())/2;
        ribbon_back->setPos(QPointF(rb_centerX,ribbon_offset+8.5));

        if(badgeType > PENGUIN::BADGE::MEMBER_0){
            chevron = new MultiCanvasObject(this);
            PROPERTIES* chevronProperties = new PROPERTIES();
            if(badgeType== PENGUIN::BADGE::MEMBER_1){
                chevronProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.chevron.member_1");
            } else if(badgeType== PENGUIN::BADGE::MEMBER_2){
                chevronProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.chevron.member_2");
            } else if(badgeType== PENGUIN::BADGE::MEMBER_3){
                chevronProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.chevron.member_3");
            } else if(badgeType== PENGUIN::BADGE::MEMBER_4){
                chevronProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.member.chevron.member_4");
            }
            chevron->initFrames(chevronProperties->filePath,chevronProperties);
            chevron->setCurrentFrames(chevronProperties);
            chevron->setFrame(0);
            chevron->setZValue(2);
            float chevron_centerX = (boundingRect().width()-chevron->boundingRect().width())/2;
            chevron->setPos(QPointF(chevron_centerX,ribbon_offset+18.5));
        }
    } else if(badgeType == PENGUIN::BADGE::PLAYER){
        backgroundProperties = new PROPERTIES();
        backgroundProperties->filePath = am->getAssetPath("interface.widgets.playercard.badge.player");
        initFrames(backgroundProperties->filePath,backgroundProperties);
        setCurrentFrames(backgroundProperties);
        setFrame(0);
    } else if(badgeType == PENGUIN::BADGE::NONE){

    } else {
        // NON-REGISTERED BADGE
    }

    setScale(0.45);
}

void Badge::clearBadge(){
    if(flashy != nullptr){
        delete flashy;
        flashy = nullptr;
    }
    if(star != nullptr){
        delete star;
        star = nullptr;
    }
    if(ribbon_front != nullptr){
        delete ribbon_front;
        ribbon_front = nullptr;
    }
    if(ribbon_back != nullptr){
        delete ribbon_back;
        ribbon_back = nullptr;
    }
    if(chevron != nullptr){
        delete chevron;
        chevron = nullptr;
    }
    clearFrames();
}
