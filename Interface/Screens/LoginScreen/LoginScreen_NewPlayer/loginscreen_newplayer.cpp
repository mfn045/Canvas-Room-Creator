#include "loginscreen_newplayer.h"

LoginScreen_NewPlayer::LoginScreen_NewPlayer(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    LocalizationManager* lm = LocalizationManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.screens.loadingscreen.screen");
    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);
    setZValue(1000);

    GridContainer* container = new GridContainer(this);
    container->setTopMargin(50);
    container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
    container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);

    TextLabel* username_label = new TextLabel();
    username_label->setText(lm->getText("login_screen.penguin_name"));
    GRIDCONTAINER::CELL_PROPERTIES* cell0 = container->addGridItem(username_label,0,0);
    cell0->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::RIGHT;

    TextInput* username_input = new TextInput();
    GRIDCONTAINER::CELL_PROPERTIES* cell0b = container->addGridItem(username_input,0,1);
    cell0b->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;


    TextLabel* password_label = new TextLabel();
    password_label->setText(lm->getText("login_screen.password"));
    GRIDCONTAINER::CELL_PROPERTIES* cell1 = container->addGridItem(password_label,1,0);
    cell1->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::RIGHT;

    TextInput* password_input = new TextInput();
    if(password_input->getLineEdit()){
        password_input->getLineEdit()->getInput()->setEchoMode(QLineEdit::Password);
    }
    GRIDCONTAINER::CELL_PROPERTIES* cell1b = container->addGridItem(password_input,1,1);
    cell1b->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;



    TextLabel* remember_me_label = new TextLabel();
    remember_me_label->setText(lm->getText("login_screen.remember_me"));
    remember_me_label->getInput()->setWordWrap(false);
    GRIDCONTAINER::CELL_PROPERTIES* cell2 = container->addGridItem(remember_me_label,2,1);
    cell2->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;

    CheckBoxButton* remember_me_input = new CheckBoxButton();
    GRIDCONTAINER::CELL_PROPERTIES* cell2b = container->addGridItem(remember_me_input,2,0);
    cell2b->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::RIGHT;


    TextLabel* remember_password_label = new TextLabel();
    remember_password_label->setText(lm->getText("login_screen.remember_password"));
    remember_password_label->getInput()->setWordWrap(false);
    GRIDCONTAINER::CELL_PROPERTIES* cell3 = container->addGridItem(remember_password_label,3,1);
    cell3->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;

    CheckBoxButton* remember_password_input = new CheckBoxButton();
    GRIDCONTAINER::CELL_PROPERTIES* cell3b = container->addGridItem(remember_password_input,3,0);
    cell3b->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::RIGHT;


    LoginBlueButton* login_button = new LoginBlueButton(nullptr);
    login_button->setText(lm->getText("login_screen.login"));
    GRIDCONTAINER::CELL_PROPERTIES* cell4 = container->addGridItem(login_button,4,0,2);
    cell4->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::CENTER;

    LoginOvalButton* forgot_password = new LoginOvalButton(nullptr,LoginOvalButton::SIZE::SMALL);
    forgot_password->setText(lm->getText("login_screen.forgot_password"));
    GRIDCONTAINER::CELL_PROPERTIES* cell5 = container->addGridItem(forgot_password,5,0,2);
    cell5->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::CENTER;

    LoginOvalButton* create_account = new LoginOvalButton(nullptr,LoginOvalButton::SIZE::SMALL);
    create_account->setTransform(QTransform(1.4120483,0,0,1.9999695,0,0));
    QString str = R"(<font color="black">)";
    str += lm->getText("login_screen.dont_have_penguin");
    str += R"(</font><br><font color="white" size="4">)";
    str += lm->getText("login_screen.create_account");
    str += R"(</font>)";
    create_account->setText(str);
    GRIDCONTAINER::CELL_PROPERTIES* cell6 = container->addGridItem(create_account,6,0,2);
    cell6->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::CENTER;
    cell6->verticalAlignment = GRIDCONTAINER::VerticalAlignment::CENTER;
    container->setMaxHeight(6,create_account->sceneBoundingRect().height());

    LoginOvalButton* cp_rules = new LoginOvalButton(nullptr,LoginOvalButton::SIZE::SMALL);
    cp_rules->setText(lm->getText("login_screen.clubpenguin_rules"));
    GRIDCONTAINER::CELL_PROPERTIES* cell7 = container->addGridItem(cp_rules,7,0,2);
    cell7->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::CENTER;

    LoginOvalButton* back = new LoginOvalButton(nullptr,LoginOvalButton::SIZE::SMALL);
    back->setText(lm->getText("login_screen.back"));
    GRIDCONTAINER::CELL_PROPERTIES* cell8 = container->addGridItem(back,8,0,2);
    cell8->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::CENTER;

    container->setHorizontalSpacing(3);
    container->setVerticalSpacing(2);

    container->updateLayout();

    MultiCanvasObject* secret_note = new MultiCanvasObject(this);
    PROPERTIES* secret_note_properties = new PROPERTIES();
    secret_note_properties->filePath = am->getAssetPath("interface.screens.loginscreen.secretnote");
    secret_note->initFrames(secret_note_properties->filePath, secret_note_properties);
    secret_note->setCurrentFrames(secret_note_properties);
    secret_note->setFrame(0);
    float secret_note_centerY = boundingRect().height()*0.4;
    float secret_note_X = boundingRect().width()*0.7;
    secret_note->setPos(QPointF(secret_note_X,secret_note_centerY));


}
