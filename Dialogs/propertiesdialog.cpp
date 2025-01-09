#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

PropertiesDialog::PropertiesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PropertiesDialog)
{
    ui->setupUi(this);
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

void PropertiesDialog::on_sButton_clicked()
{
    QString filePath = getFilePath();
    ui->sLoc->setText(filePath);
    this->sLoc = ui->sLoc->text();
}


void PropertiesDialog::on_seButton_clicked()
{
    QString filePath = getFilePath();
    ui->seLoc->setText(filePath);
    this->seLoc = ui->seLoc->text();
}


void PropertiesDialog::on_eButton_clicked()
{
    QString filePath = getFilePath();
    ui->eLoc->setText(filePath);
    this->eLoc = ui->eLoc->text();
}


void PropertiesDialog::on_neButton_clicked()
{
    QString filePath = getFilePath();
    ui->neLoc->setText(filePath);
    this->neLoc = ui->neLoc->text();
}


void PropertiesDialog::on_nButton_clicked()
{
    QString filePath = getFilePath();
    ui->nLoc->setText(filePath);
    this->nLoc = ui->nLoc->text();
}


void PropertiesDialog::on_nwButton_clicked()
{
    QString filePath = getFilePath();
    ui->nwLoc->setText(filePath);
    this->nwLoc = ui->nwLoc->text();
}


void PropertiesDialog::on_wButton_clicked()
{
    QString filePath = getFilePath();
    ui->wLoc->setText(filePath);
    this->wLoc = ui->wLoc->text();
}

void PropertiesDialog::clearFilePaths(){
    ui->sLoc->setText("");
    ui->swLoc->setText("");
    ui->wLoc->setText("");
    ui->nwLoc->setText("");
    ui->nLoc->setText("");
    ui->neLoc->setText("");
    ui->eLoc->setText("");
    ui->seLoc->setText("");
}

void PropertiesDialog::updateFilePaths(){
    ui->sLoc->setText(sLoc);
    ui->swLoc->setText(swLoc);
    ui->wLoc->setText(wLoc);
    ui->nwLoc->setText(nwLoc);
    ui->nLoc->setText(nLoc);
    ui->neLoc->setText(neLoc);
    ui->eLoc->setText(eLoc);
    ui->seLoc->setText(seLoc);
}

void PropertiesDialog::on_swButton_clicked()
{
    QString filePath = getFilePath();
    ui->swLoc->setText(filePath);
    this->swLoc = ui->swLoc->text();
}

QString PropertiesDialog::getFilePath(){
    QMessageBox mb(this);
    mb.setText("Do you want to select a directory or a file?");
    mb.addButton("File",QMessageBox::NoRole);
    mb.addButton("Directory",QMessageBox::NoRole);
    mb.addButton(QMessageBox::Cancel);
    mb.setDefaultButton(QMessageBox::Cancel);
    mb.exec();
    QUrl directory;
    QString filePath = "";
    if(mb.clickedButton()->text() == "Directory"){
        filePath = QFileDialog::getExistingDirectory(this,"Select a sprite directory");
    } else if(mb.clickedButton()->text() == "File"){
        directory = QFileDialog::getOpenFileUrl(this,"Select a sprite file");
        filePath = directory.toString().replace("file:///","");
    }
    return filePath;
}

void PropertiesDialog::on_stateComboBox_currentTextChanged(const QString &state)
{
    this->state = state;
    emit stateChanged();
}

QString PropertiesDialog::getSLoc(){
    return this->sLoc;
}
QString PropertiesDialog::setSLoc(QString sLoc){
    this->sLoc = sLoc;
    return this->sLoc;
}

QString PropertiesDialog::getSELoc(){
    return this->seLoc;
}

QString PropertiesDialog::setSELoc(QString seLoc){
    this->seLoc = seLoc;
    return this->seLoc;
}

QString PropertiesDialog::getELoc(){
    return this->eLoc;
}
QString PropertiesDialog::setELoc(QString eLoc){
    this->eLoc = eLoc;
    return this->eLoc;
}

QString PropertiesDialog::getNELoc(){
    return this->neLoc;
}

QString PropertiesDialog::setNELoc(QString neLoc){
    this->neLoc = neLoc;
    return this->neLoc;
}

QString PropertiesDialog::getNLoc(){
    return this->nLoc;
}

QString PropertiesDialog::setNLoc(QString nLoc){
    this->nLoc = nLoc;
    return this->nLoc;
}

QString PropertiesDialog::getNWLoc(){
    return this->nwLoc;
}
QString PropertiesDialog::setNWLoc(QString nwLoc){
    this->nwLoc = nwLoc;
    return this->nwLoc;
}

QString PropertiesDialog::getWLoc(){
    return this->wLoc;
}

QString PropertiesDialog::setWLoc(QString wLoc){
    this->wLoc = wLoc;
    return this->wLoc;
}

QString PropertiesDialog::getSWLoc(){
    return this->swLoc;
}

QString PropertiesDialog::setSWLoc(QString swLoc){
    this->swLoc = swLoc;
    return this->swLoc;
}

QString PropertiesDialog::getState(){
    return this->state;
}
QString PropertiesDialog::setState(QString state){
    this->state = state;
    return this->state;
}
