#ifndef YESNODIALOG_H
#define YESNODIALOG_H

#include <QGraphicsView>
#include "Interface/Widgets/Dialogs/abstractdialog.h"
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"
#include "Interface/Widgets/Buttons/BlueButton/bluebutton.h"
#include "Interface/Widgets/Buttons/OrangeButton/orangebutton.h"


class YesNoDialog : public AbstractDialog
{
public:
    explicit YesNoDialog(Scene* parent = nullptr, TYPE type = TYPE::BLUE);
    bool initDialog();
};

#endif // YESNODIALOG_H
