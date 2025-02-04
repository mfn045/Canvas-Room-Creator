#include "badge.h"

Badge::Badge(MultiCanvasObject* parent, PENGUIN::BADGE badgeType) {

    if(badgeType == PENGUIN::BADGE::MEMBER_0
        || badgeType == PENGUIN::BADGE::MEMBER_1
        || badgeType == PENGUIN::BADGE::MEMBER_2
        || badgeType == PENGUIN::BADGE::MEMBER_3
        || badgeType == PENGUIN::BADGE::MEMBER_4){
        PROPERTIES* backgroundProperties = new PROPERTIES();
        backgroundProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/background/1.svg";
        initFrames(backgroundProperties->filePath,backgroundProperties);
        setCurrentFrames(backgroundProperties);
        setFrame(0);

        MaskedMultiCanvasObject* flashy = new MaskedMultiCanvasObject(this);
        flashy->setHasAnimationLoop(true);
        flashy->setMask("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/flashy_mask.svg");
        flashy->getRegion().translate(QPoint(323,381));
        PROPERTIES* flashyProperties = new PROPERTIES();
        flashyProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/flashy";
        flashy->initFrames(flashyProperties->filePath,flashyProperties);
        flashy->setCurrentFrames(flashyProperties);
        flashy->setFrame(0);
        flashy->setScale(0.215);
        flashy->setZValue(0);
        float flash_centerX = (boundingRect().width()-flashy->sceneBoundingRect().width())/2;
        int flash_centerY = -flashy->sceneBoundingRect().height()+(1.5*boundingRect().height());
        flashy->setPos(QPointF(flash_centerX,flash_centerY));

        MultiCanvasObject* star = new MultiCanvasObject(this);
        PROPERTIES* starProperties = new PROPERTIES();
        starProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/star/1.svg";
        star->initFrames(starProperties->filePath,starProperties);
        star->setCurrentFrames(starProperties);
        star->setFrame(0);
        star->setZValue(1);
        float star_centerX = (boundingRect().width()-star->sceneBoundingRect().width())/2;
        star->setPos(QPointF(star_centerX,10));

        float ribbon_offset = 50;

        MultiCanvasObject* ribbon_front = new MultiCanvasObject(this);
        PROPERTIES* rfProperties = new PROPERTIES();
        rfProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/ribbon_front/en.svg";
        ribbon_front->initFrames(rfProperties->filePath,rfProperties);
        ribbon_front->setCurrentFrames(rfProperties);
        ribbon_front->setFrame(0);
        ribbon_front->setZValue(3);
        float rf_centerX = (boundingRect().width()-ribbon_front->sceneBoundingRect().width())/2;
        ribbon_front->setPos(QPointF(rf_centerX,ribbon_offset));

        MultiCanvasObject* ribbon_back = new MultiCanvasObject(this);
        ribbon_back->setFlag(QGraphicsSvgItem::GraphicsItemFlag::ItemStacksBehindParent);
        PROPERTIES* rbProperties = new PROPERTIES();
        rbProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/ribbon_back/1.svg";
        ribbon_back->initFrames(rbProperties->filePath,rbProperties);
        ribbon_back->setCurrentFrames(rbProperties);
        ribbon_back->setFrame(0);
        float rb_centerX = (boundingRect().width()-ribbon_back->sceneBoundingRect().width())/2;
        ribbon_back->setPos(QPointF(rb_centerX,ribbon_offset+8.5));

        if(badgeType > PENGUIN::BADGE::MEMBER_0){
            MultiCanvasObject* chevron = new MultiCanvasObject(this);
            PROPERTIES* chevronProperties = new PROPERTIES();
            QString chevronPath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/member/chevron/";
            if(badgeType== PENGUIN::BADGE::MEMBER_1){
                chevronPath += "member_1";
            } else if(badgeType== PENGUIN::BADGE::MEMBER_2){
                chevronPath += "member_2";
            } else if(badgeType== PENGUIN::BADGE::MEMBER_3){
                chevronPath += "member_3";
            } else if(badgeType== PENGUIN::BADGE::MEMBER_4){
                chevronPath += "member_4";
            }
            chevronPath += ".svg";
            chevronProperties->filePath = chevronPath;
            chevron->initFrames(chevronProperties->filePath,chevronProperties);
            chevron->setCurrentFrames(chevronProperties);
            chevron->setFrame(0);
            chevron->setZValue(2);
            float chevron_centerX = (boundingRect().width()-chevron->sceneBoundingRect().width())/2;
            chevron->setPos(QPointF(chevron_centerX,ribbon_offset+18.5));
        }
    } else if(badgeType == PENGUIN::BADGE::PLAYER){
        PROPERTIES* backgroundProperties = new PROPERTIES();
        backgroundProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/badge/player/1.svg";
        initFrames(backgroundProperties->filePath,backgroundProperties);
        setCurrentFrames(backgroundProperties);
        setFrame(0);
    } else if(badgeType == PENGUIN::BADGE::NONE){

    } else {
        // NON-REGISTERED BADGE
    }

    setScale(0.45);
}
