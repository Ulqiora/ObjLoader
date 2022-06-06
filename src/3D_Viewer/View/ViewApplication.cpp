#include "ViewApplication.h"
#include "ui_ViewApplication.h"

ViewApplication::ViewApplication(SettingsView* set,s21::Facade* new_facade,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewApplication)
{
    _facade=new_facade;
    settings=set;
    ui->setupUi(this);
    ui->MyOpenGLWidget->setFacade(new_facade);
    connect(this,&ViewApplication::RotateValueXEdited,ui->MyOpenGLWidget,&OpenGL::rotateX);
    connect(this,&ViewApplication::RotateValueYEdited,ui->MyOpenGLWidget,&OpenGL::rotateY);
    connect(this,&ViewApplication::RotateValueZEdited,ui->MyOpenGLWidget,&OpenGL::rotateZ);
    connect(this,&ViewApplication::MoveValueXEdited,ui->MyOpenGLWidget,&OpenGL::moveX);
    connect(this,&ViewApplication::MoveValueYEdited,ui->MyOpenGLWidget,&OpenGL::moveY);
    connect(this,&ViewApplication::MoveValueZEdited,ui->MyOpenGLWidget,&OpenGL::moveZ);
    connect(this,&ViewApplication::ScaleValueEdited,ui->MyOpenGLWidget,&OpenGL::scale);
    connect(this->settings,&SettingsView::updateImage,ui->MyOpenGLWidget,&OpenGL::reloadFigure);
    connect(ui->MyOpenGLWidget,&OpenGL::mouseSignal,this,&ViewApplication::updateUi);
}

ViewApplication::~ViewApplication()
{
    delete ui;
}

void ViewApplication::on_ChooseFileButton_clicked()
{
    QString str=QFileDialog::getOpenFileName(this,"Выбрать файл","","Файлы изображений (* .obj )");
    if (str!=""){
        ui->FullFileName->setText(str);
        _facade->getFigure()->initByObjFile(str);
        ui->NumOfEdges->setText(QString::number(_facade->getFigure()->getData()->getSizeIndices()));
        ui->NumOfVertices->setText(QString::number(_facade->getFigure()->getData()->getSizeVertices()));
    }
    ui->MyOpenGLWidget->update();
}

void ViewApplication::on_SettingsButton_clicked()
{
    settings->show();
}

void ViewApplication::on_SliderMoveX_valueChanged(int value)
{
    ui->SliderMoveXValue->setText(QString::fromStdString(std::to_string( value/100.0)));
    emit MoveValueXEdited(value);
}


void ViewApplication::on_SliderMoveY_valueChanged(int value)
{
    ui->SliderMoveYValue->setText(QString::fromStdString(std::to_string( value/100.0)));
    emit MoveValueYEdited(value);
}

void ViewApplication::on_SliderMoveZ_valueChanged(int value)
{
    ui->SliderMoveZValue->setText(QString::fromStdString(std::to_string( value/100.0)));
    emit MoveValueZEdited(value);
}


void ViewApplication::on_SliderScale_valueChanged(int value)
{
    ui->SliderScaleValue->setText(QString::fromStdString(std::to_string( value/10000.0)));
    emit ScaleValueEdited(value);
}


void ViewApplication::on_SliderRotateX_valueChanged(int value)
{
    ui->SliderRotateXValue->setText(QString::fromStdString(std::to_string( value)));
    emit RotateValueXEdited(value);
}


void ViewApplication::on_SliderRotateY_valueChanged(int value)
{
    ui->SliderRotateYValue->setText(QString::fromStdString(std::to_string( value)));
    emit RotateValueYEdited(value);
}


void ViewApplication::on_SliderRotateZ_valueChanged(int value)
{
    ui->SliderRotateZValue->setText(QString::fromStdString(std::to_string( value)));
    emit RotateValueZEdited(value);
}

void ViewApplication::on_pushButton_clicked()
{
    QString file=QFileDialog::getExistingDirectory();
}


void ViewApplication::on_ScreenButton_clicked()
{
    QString screenshotFileName = QFileDialog::getSaveFileName(this,"Сохранить в файл","./","Images(* .png * .jpeg)");
    if (screenshotFileName!=""){
        ui->MyOpenGLWidget->grab().save(screenshotFileName);
    }
}

void ViewApplication::updateUi()
{
    ui->SliderMoveXValue->setText(QString::fromStdString(std::to_string(_facade->getFigure()->getManipulation()._move[X])));
    ui->SliderMoveYValue->setText(QString::fromStdString(std::to_string(_facade->getFigure()->getManipulation()._move[Y])));
    ui->SliderRotateXValue->setText(QString::fromStdString(std::to_string(_facade->getFigure()->getManipulation()._rotate[X])));
    ui->SliderRotateYValue->setText(QString::fromStdString(std::to_string(_facade->getFigure()->getManipulation()._rotate[Y])));
    ui->SliderScaleValue->setText(QString::fromStdString(std::to_string(_facade->getFigure()->getManipulation()._scale/10000)));
}

void ViewApplication::updateSettings()
{
    _facade->getSettings()->initByFileConf(FileType::CUSTOM);
}

