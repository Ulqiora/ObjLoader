#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QMainWindow>
#include <QDialog>
#include <QColorDialog>
#include <QCloseEvent>
#include <QFile>
//#include <fstream>
#include <QDebug>
#include <qurl.h>
#include <QTextStream>
#include <QDir>
#include <iostream>
#include "../Models/Settings_t.h"
namespace Ui {
class SettingsView;
}

class SettingsView : public QDialog
{
    Q_OBJECT
public:
    SettingsView(Settings_t* settings,QWidget *parent = nullptr);
    void initByFileConf(FileType fileId);
    ~SettingsView();
private slots:
    void on_SettingsButtonColorEdge_clicked();

    void on_SettingButtonColorVer_clicked();

    void on_SettingsButtonColorBack_clicked();

    void on_SettingsButtonReset_clicked();

    void on_SettingsButtonOK_clicked();

    void on_SettingsButtonThickness_valueChanged(int arg1);

    void on_SettingsButtonSize_valueChanged(int arg1);

    void on_SettingsButtonShape_currentIndexChanged(int index);

    void on_SettinngsButtonType_currentIndexChanged(int index);

private:
    SettingsView(SettingsView const&) = delete;
    SettingsView(SettingsView const&&) = delete;
    SettingsView& operator=(SettingsView const&) = delete;
    SettingsView& operator=(SettingsView const&&) = delete;
    void closeEvent(QCloseEvent*)override;
private:
    Ui::SettingsView *ui;
    Settings_t* _settingsInfo;
    void saveSettingsByConf();
    void initUIbySettings();
signals:
    void updateSettings();
    void updateImage();
};

#endif // SETTINGSVIEW_H
