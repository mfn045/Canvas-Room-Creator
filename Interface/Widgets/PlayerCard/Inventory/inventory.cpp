#include "inventory.h"

Inventory::Inventory(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    PROPERTIES* invProperties = new PROPERTIES();
    invProperties->filePath = am->getAssetPath("interface.widgets.playercard.inventory.inventory_background");
    setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    initFrames(invProperties->filePath,invProperties);
    setCurrentFrames(invProperties);
    setFrame(0);
    setZValue(0);
    QTransform invTransform = transform();
    invTransform.setMatrix(0.975,invTransform.m12(),invTransform.m13(),
                           invTransform.m21(),0.975,invTransform.m23(),
                           invTransform.m31(),invTransform.m32(),invTransform.m33());
    setTransform(invTransform);
    if(parent){
        setPos(QPointF(50,parent->boundingRect().height()-5));
    }


    GridContainer* items = new GridContainer(this);
    items->setTopMargin(10);
    items->setRightMargin(5);
    items->setVerticalSpacing(5);
    items->setHorizontalSpacing(5);
    items->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::RIGHT);
    items->setScale(0.975);

    int i = 0;
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 3; c++){
            WhiteSquareButton* button = new WhiteSquareButton(nullptr,WhiteSquareButton::SIZE::MEDIUM);
            items->addGridItem(button,r,c);
            inventoryItems.insert(i,button);
            i++;
        }
    }

    loadInventoryPage(1);

    MultiCanvasObject* scrollBar = new MultiCanvasObject();
    PROPERTIES* scrollBarProperties = new PROPERTIES();
    scrollBarProperties->filePath = am->getAssetPath("interface.widgets.playercard.inventory.whitescrollrect");
    scrollBar->initFrames(scrollBarProperties->filePath,scrollBarProperties);
    scrollBar->setCurrentFrames(scrollBarProperties);
    scrollBar->setFrame(0);

    items->addGridItem(scrollBar,0,3,1,4);

    CircleButton* scrollUpButton = new CircleButton(scrollBar,CircleButton::COLOR::WHITE);
    scrollUpButton->setIcon(am->getAssetPath("interface.icons.whitearrows.up"));
    scrollUpButton->setPos(QPointF(0,-(scrollUpButton->boundingRect().height()/2)));
    scrollUpButton->connect(scrollUpButton, &CircleButton::clicked, [this](){
        loadInventoryPage(--currentInventoryPage , sort);
    });

    CircleButton* scrollDownButton = new CircleButton(scrollBar,CircleButton::COLOR::WHITE);
    scrollDownButton->setIcon(am->getAssetPath("interface.icons.whitearrows.down"));
    scrollDownButton->setPos(QPointF(0,scrollBar->boundingRect().height()-(scrollUpButton->boundingRect().height()/2)));
    scrollDownButton->connect(scrollDownButton, &CircleButton::clicked, [this](){
        loadInventoryPage(++currentInventoryPage, sort);
    });

    items->updateLayout();

    LocalizationManager* lm = LocalizationManager::getInstance();
    CategoryButton* category = new CategoryButton(this);
    category->getButton()->setText(lm->getText("playercard.all_items"));
    category->setPos(QPointF(boundingRect().width()-212,boundingRect().height()-18.5));

    GridContainer* categories = new GridContainer(category);
    categories->hide();
    if(category->getButton() != nullptr){
        category->getButton()->connect(category->getButton(),&OvalButton::clicked, [categories](){
            if(categories != nullptr){
                if(categories->isVisible()){
                    categories->hide();
                } else {
                    categories->show();
                }
            }
        });
    }

    int categories_verticalSpacing = 2;
    categories->setVerticalSpacing(categories_verticalSpacing);
    categories->setBottomMargin(3);

    WhiteRectButton* otherSort = new WhiteRectButton(nullptr,WhiteRectButton::SIZE::SMALL,WhiteRectButton::TYPE::WITH_ARROW);
    otherSort->setText(lm->getText("playercard.other_items"));
    categories->addGridItem(otherSort,7,0);

    //--------
    GridContainer* otherCategory = new GridContainer(otherSort);
    otherCategory->hide();
    otherCategory->setVerticalSpacing(categories_verticalSpacing);

    auto hideAllCategories = [otherCategory,categories](){
        if(otherCategory != nullptr){
            otherCategory->setVisible(false);
        }
        if(categories != nullptr){
            categories->setVisible(false);
        }
    };

    WhiteRectButton* pinFlagSort = new WhiteRectButton();
    pinFlagSort->setText(lm->getText("playercard.pins_flags_items"));
    otherCategory->addGridItem(pinFlagSort,0,0);
    pinFlagSort->connect(pinFlagSort, &WhiteRectButton::clicked, [otherSort,pinFlagSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(pinFlagSort){
            pinFlagSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(otherSort){
            otherSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.pins_flags_items"));
        }
        sortItemsBy(INVENTORY::SORT::PIN);
    });

    WhiteRectButton* awardsSort = new WhiteRectButton();
    awardsSort->setText(lm->getText("playercard.award_items"));
    otherCategory->addGridItem(awardsSort,1,0);
    awardsSort->connect(awardsSort, &WhiteRectButton::clicked, [otherSort,awardsSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(awardsSort){
            awardsSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(otherSort){
            otherSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.award_items"));
        }
        sortItemsBy(INVENTORY::SORT::AWARD);
    });

    WhiteRectButton* backgroundSort = new WhiteRectButton();
    backgroundSort->setText(lm->getText("playercard.background_items"));
    otherCategory->addGridItem(backgroundSort,2,0);
    backgroundSort->connect(backgroundSort, &WhiteRectButton::clicked, [otherSort,backgroundSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(backgroundSort){
            backgroundSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(otherSort){
            otherSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.background_items"));
        }
        sortItemsBy(INVENTORY::SORT::BACKGROUND);
    });

    otherCategory->addCallbackFunction([otherSort,otherCategory,categories_verticalSpacing](){
        float otherCategory_centerX = otherSort->boundingRect().width()+categories_verticalSpacing;
        float otherCategory_centerY = (otherCategory->getHeight()-otherSort->boundingRect().height())/2;
        otherCategory->setPos(QPointF(otherCategory_centerX,-otherCategory_centerY));
    });

    otherCategory->updateLayout();

    //--------
    otherSort->connect(otherSort,&WhiteRectButton::clicked,[otherCategory](){
        if(otherCategory != nullptr){
            if(otherCategory->isVisible()){
                otherCategory->show();
            } else {
                otherCategory->show();
            }
        }
    });

    WhiteRectButton* headSort = new WhiteRectButton();
    headSort->setText(lm->getText("playercard.head_items"));
    categories->addGridItem(headSort,0,0);
    headSort->connect(headSort, &WhiteRectButton::clicked, [headSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(headSort){
            headSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.head_items"));
        }
        sortItemsBy(INVENTORY::SORT::HEAD);
    });

    WhiteRectButton* faceSort = new WhiteRectButton();
    faceSort->setText(lm->getText("playercard.face_items"));
    categories->addGridItem(faceSort,1,0);
    faceSort->connect(faceSort, &WhiteRectButton::clicked, [faceSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(faceSort){
            faceSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.face_items"));
        }
        sortItemsBy(INVENTORY::SORT::FACE);
    });

    WhiteRectButton* neckSort = new WhiteRectButton();
    neckSort->setText(lm->getText("playercard.neck_items"));
    categories->addGridItem(neckSort,2,0);
    neckSort->connect(neckSort, &WhiteRectButton::clicked, [neckSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(neckSort){
            neckSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.neck_items"));
        }
        sortItemsBy(INVENTORY::SORT::NECK);
    });

    WhiteRectButton* bodySort = new WhiteRectButton();
    bodySort->setText(lm->getText("playercard.body_items"));
    categories->addGridItem(bodySort,3,0);
    bodySort->connect(bodySort, &WhiteRectButton::clicked, [bodySort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(bodySort){
            bodySort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.body_items"));
        }
        sortItemsBy(INVENTORY::SORT::BODY);
    });

    WhiteRectButton* handSort = new WhiteRectButton();
    handSort->setText(lm->getText("playercard.hand_items"));
    categories->addGridItem(handSort,4,0);
    handSort->connect(handSort, &WhiteRectButton::clicked, [handSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(handSort){
            handSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.hand_items"));
        }
        sortItemsBy(INVENTORY::SORT::HAND);
    });

    WhiteRectButton* feetSort = new WhiteRectButton();
    feetSort->setText(lm->getText("playercard.feet_items"));
    categories->addGridItem(feetSort,5,0);
    feetSort->connect(feetSort, &WhiteRectButton::clicked, [feetSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(feetSort){
            feetSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.feet_items"));
        }
        sortItemsBy(INVENTORY::SORT::FEET);
    });

    WhiteRectButton* colorSort = new WhiteRectButton();
    colorSort->setText(lm->getText("playercard.color_items"));
    categories->addGridItem(colorSort,6,0);
    colorSort->connect(colorSort, &WhiteRectButton::clicked, [colorSort,lm,hideAllCategories,category,this](){
        hideAllCategories();
        if(colorSort){
            colorSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.color_items"));
        }
        sortItemsBy(INVENTORY::SORT::COLOR);
    });

    WhiteRectButton* allSort = new WhiteRectButton();
    allSort->setText(lm->getText("playercard.all_items"));
    categories->addGridItem(allSort,8,0);
    allSort->connect(allSort, &WhiteRectButton::clicked, [lm,allSort,hideAllCategories,category,this](){
        hideAllCategories();
        if(allSort){
            allSort->setCurrentState(WhiteRectButton::STATE::UP);
        }
        if(category && lm){
            category->getButton()->setText(lm->getText("playercard.all_items"));
        }
        sortItemsBy(INVENTORY::SORT::ALL);
    });

    categories->addCallbackFunction([category,categories](){
        if(category && categories){
            float category_centerX = (category->boundingRect().width()-categories->getWidth())/2;
            categories->setPos(QPointF(category_centerX,-categories->getHeight()));
        }
    });


    categories->updateLayout();
}

void Inventory::loadInventoryPage(int page, INVENTORY::SORT sort){
    if(player == nullptr) return;
    if(page < 1){
        page = 1;
        currentInventoryPage = page;
    }
    int i = 0;

    QList<int> appropriateIds = {};
    Items* instance = Items::getInstance();
    QList<int> ownedItems = player->getOwnedItems();
    for(auto items = ownedItems.begin(); items != ownedItems.end(); items++){
        if(!instance->exists(*items)){ qDebug() << "ITEM DONT EXIST SKIPPING " << *items; continue; } else { qDebug() << "ITEM EXISTS " << *items; }
        if(instance->getType(*items) == sort || sort == INVENTORY::SORT::ALL){
            appropriateIds.append(*items);
        }
    }
    for(int k = 0; k < 12; k++){
        WhiteSquareButton* button = inventoryItems.value(k);
        button->setDisabled(true);
        if(button->getIcon()){
            button->getIcon()->clearFrames();
        }
    }
    if(appropriateIds.empty()) return;
    int maxPages = ceil(appropriateIds.size()/12)+1;
    if(page > maxPages){
        page = maxPages;
        currentInventoryPage = page;
    }
    int initialIndex = 0+((page-1)*12);
    for(int itemIndex = initialIndex; itemIndex <= initialIndex+12; itemIndex++){
        if(i == 12) break;
        if((appropriateIds.size()) > itemIndex){
            qDebug() << "Item Index " << itemIndex << (appropriateIds.size()-1);
            int itemId = appropriateIds[itemIndex];
            WhiteSquareButton* button = inventoryItems.value(i);
            button->setDisabled(false);
            button->setIcon("C:/Users/mfn45/OneDrive/Desktop/Clothings/1-499/items/" + QString::number(itemId) + "/icon/1.svg");
            button->disconnect();
            button->connect(button, &WhiteSquareButton::clicked, [=](){
                qDebug() << "Clicked " << itemId;
                Items* items = Items::getInstance();
                int type = items->getType(itemId);
                if(type == Clothes::TYPE::HEAD){
                    player->getPenguinPaper()->setHead(itemId);
                    player->getPenguinSprite()->setHead(itemId);
                    qDebug() << "Head";
                }else if(type == Clothes::TYPE::FACE){
                    player->getPenguinPaper()->setFace(itemId);
                    player->getPenguinSprite()->setFace(itemId);
                    qDebug() << "face";
                }else if(type == Clothes::TYPE::NECK){
                    player->getPenguinPaper()->setNeck(itemId);
                    player->getPenguinSprite()->setNeck(itemId);
                    qDebug() << "neck";
                }else if(type == Clothes::TYPE::BODY){
                    player->getPenguinPaper()->setBody(itemId);
                    player->getPenguinSprite()->setBody(itemId);
                    qDebug() << "body";
                }else if(type == Clothes::TYPE::HAND){
                    player->getPenguinPaper()->setHand(itemId);
                    player->getPenguinSprite()->setHand(itemId);
                    qDebug() << "hand";
                }else if(type == Clothes::TYPE::FEET){
                    player->getPenguinPaper()->setFeet(itemId);
                    player->getPenguinSprite()->setFeet(itemId);
                    qDebug() << "feeet";
                }else if(type == Clothes::TYPE::PIN){
                    player->getPenguinPaper()->setPin(itemId);
                    qDebug() << "pin";
                }else if(type == Clothes::TYPE::BACKGROUND){
                    player->getPenguinPaper()->setBackground(itemId);
                    qDebug() << "bg";
                }else if(type == Clothes::TYPE::COLOR){
                    player->getPenguinPaper()->setColor(itemId);
                }
            });
        } else {
            WhiteSquareButton* button = inventoryItems.value(i);
            button->disconnect();
            if(button->getIcon()){
                button->getIcon()->clearFrames();
            }
        }
        i++;
    }
}

Player* Inventory::setPlayer(Player* player){
    this->player = player;
    loadInventoryPage(1);
    return this->player;
}

INVENTORY::SORT Inventory::sortItemsBy(INVENTORY::SORT sort){
    this->sort = sort;
    this->currentInventoryPage = 1;
    loadInventoryPage(currentInventoryPage,sort);
    return this->sort;
}
