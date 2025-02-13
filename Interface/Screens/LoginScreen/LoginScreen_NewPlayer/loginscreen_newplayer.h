#ifndef LOGINSCREEN_NEWPLAYER_H
#define LOGINSCREEN_NEWPLAYER_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Common/TextLineEdit/textlineedit.h"
#include "Interface/Screens/LoginScreen/Buttons/LoginBlueButton/loginbluebutton.h"
#include "Interface/Screens/LoginScreen/Buttons/LoginOvalButton/loginovalbutton.h"
#include "Interface/Widgets/Inputs/TextInput/textinput.h"
#include "Interface/Widgets/Buttons/CheckBoxButton/checkboxbutton.h"

class LoginScreen_NewPlayer : public MultiCanvasObject
{
public:
    explicit LoginScreen_NewPlayer(MultiCanvasObject* parent = nullptr);

signals:
    void clickedForgotPassword();
    void clickedCreateAccount();
    void clickedRules();
    void clickedBack();
    void clickedRememberMe();
    void clickedRememberMyPassword();
};

#endif // LOGINSCREEN_NEWPLAYER_H
