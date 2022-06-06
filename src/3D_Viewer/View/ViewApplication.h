#ifndef VIEWAPPLICATION_H
#define VIEWAPPLICATION_H

#include <QMainWindow>
#include <QFileDialog>
#include "../Controller/Controller.h"
#include "../View/SettingsView.h"
#include "../CustomWidget/CustomOpenGL.h"
#include <iostream>
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class ViewApplication; }
QT_END_NAMESPACE

class ViewApplication : public QMainWindow
{
    Q_OBJECT

public:
    ViewApplication(SettingsView* set,s21::Facade* new_facade, QWidget *parent = nullptr);
    ~ViewApplication();

private slots:

    void on_ChooseFileButton_clicked();
    void on_SettingsButton_clicked();
    void on_SliderRotateX_valueChanged(int value);
    void on_SliderMoveX_valueChanged(int value);
    void on_SliderMoveY_valueChanged(int value);
    void on_SliderMoveZ_valueChanged(int value);
    void on_SliderRotateY_valueChanged(int value);
    void on_SliderRotateZ_valueChanged(int value);
    void on_SliderScale_valueChanged(int value);
    void on_pushButton_clicked();
    void on_ScreenButton_clicked();

private:
    Ui::ViewApplication *ui;
    s21::Facade* _facade;
    SettingsView* settings;
signals:
    void RotateValueXEdited(double);
    void RotateValueYEdited(double);
    void RotateValueZEdited(double);
    void MoveValueXEdited(double);
    void MoveValueYEdited(double);
    void MoveValueZEdited(double);
    void ScaleValueEdited(double);
public slots:
    void updateUi();
    void updateSettings();
};
#endif // VIEWAPPLICATION_H
