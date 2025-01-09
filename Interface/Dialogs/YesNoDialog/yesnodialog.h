#ifndef YESNODIALOG_H
#define YESNODIALOG_H

#include "../abstractdialog.h"
#include "../../Buttons/AbstractButton/abstractbutton.h"
#include "../../Buttons/BlueButton/bluebutton.h"
#include "../../SvgGridContainer/gridcontainer.h"
#include "../../Buttons/OrangeButton/orangebutton.h"
#include <QGraphicsView>


class YesNoDialog : public AbstractDialog
{
public:
    explicit YesNoDialog(Scene* parent = nullptr, TYPE type = TYPE::BLUE);
    bool initDialog();
};

#endif // YESNODIALOG_H
