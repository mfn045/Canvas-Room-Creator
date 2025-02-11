#include "settings.h"

Settings::Settings(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    DialogGrid* grid = new DialogGrid();
    grid->setWidth(300);
    grid->setHeight(300);
    grid->init();
    grid->setParentItem(this);

    GridContainer* container = new GridContainer(grid);

    container->setTopMargin(15);
    container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
    container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::TOP);

    TitleLabel* label = new TitleLabel();
    label->setText("Settings");
    container->addGridItem(label,0,0);


    TextLabel* serverLabel = new TextLabel();
    QFont font = serverLabel->getInput()->font();
    font.setFamily("Burbank Small Black");
    serverLabel->getInput()->setFont(font);
    serverLabel->setText("You're on Server Name");
    container->addGridItem(serverLabel,1,0);

    TextLabel* ageLabel = new TextLabel();
    QFont font2 = ageLabel->getInput()->font();
    font2.setFamily("Burbank Small Black");
    ageLabel->getInput()->setFont(font2);
    ageLabel->setText("Your penguin is 252 days old");
    container->addGridItem(ageLabel,2,0);


    container->updateLayout();
}
