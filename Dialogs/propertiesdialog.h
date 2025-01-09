#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesDialog(QWidget *parent = nullptr);
    ~PropertiesDialog();
    void updateFilePaths();
    void clearFilePaths();

    QString getFilePath();

    QString getSLoc();
    QString setSLoc(QString sLoc);

    QString getSELoc();
    QString setSELoc(QString seLoc);

    QString getELoc();
    QString setELoc(QString eLoc);

    QString getNELoc();
    QString setNELoc(QString neLoc);

    QString getNLoc();
    QString setNLoc(QString nLoc);

    QString getNWLoc();
    QString setNWLoc(QString nwLoc);

    QString getWLoc();
    QString setWLoc(QString wLoc);

    QString getSWLoc();
    QString setSWLoc(QString wLoc);

    QString getState();
    QString setState(QString state);

private slots:
    void on_sButton_clicked();

    void on_seButton_clicked();

    void on_eButton_clicked();

    void on_neButton_clicked();

    void on_nButton_clicked();

    void on_nwButton_clicked();

    void on_wButton_clicked();

    void on_swButton_clicked();

    void on_stateComboBox_currentTextChanged(const QString &state);

private:
    Ui::PropertiesDialog *ui;
    QString sLoc = "";
    QString seLoc = "";
    QString eLoc = "";
    QString neLoc = "";
    QString nLoc = "";
    QString nwLoc = "";
    QString wLoc = "";
    QString swLoc = "";
    QString state = "";

signals:
    void stateChanged();
};

#endif // PROPERTIESDIALOG_H
