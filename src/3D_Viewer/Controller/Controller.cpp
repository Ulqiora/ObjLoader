#pragma once
#include "Controller.h"
namespace s21 {

Figure* Facade::getFigure(){
    return F;
}

void Facade::updateModel(QString file_name){
    //проверка на наличие данного файла и его расширения.
    F->initByObjFile(file_name);
}
Settings_t* Facade::getSettings(){
    return _settings;
}

Matrix Facade::getMvpMatrix(){
    Matrix  MatrixModel = s21::TransformMatrixBuilder::CreateRotateMatrix(F->getManipulation()._rotate[X]/180.0*M_PI,F->getManipulation()._rotate[Y]/180.0*M_PI,F->getManipulation()._rotate[Z]/180.0*M_PI);
            MatrixModel = s21::TransformMatrixBuilder::CreateMoveMatrix(F->getManipulation()._move[X]/100.0,F->getManipulation()._move[Y]/100.0,F->getManipulation()._move[Z]/100.0) * MatrixModel;
            MatrixModel = s21::TransformMatrixBuilder::CreateScaleMatrix(F->getManipulation()._scale/10000.0) * MatrixModel;
    Matrix MatrixView = s21::TransformMatrixBuilder::CreateViewMatrix();
    Matrix MatrixProjection;
    if(_settings->_projectionType==ProjectionType::CENTRAL)
        MatrixProjection = s21::TransformMatrixBuilder::CreatePerspectiveMatrix((45.0/180.0)*M_PI, 1.2, 0.1, 1000.0);
    else {
        MatrixProjection = s21::TransformMatrixBuilder::CreateOrthoMatrix(F->getExtremum());
    }
//    Matrix MatrixProjection=s21::TransformMatrixBuilder::CreateOrthoMatrix(F->getExtremum());
//    QMatrix4x4 MP(MatrixProjection.getMass(),4,4);
//    qDebug()<<MP;
//    MP.setToIdentity();
//    MP.ortho(F->getExtremum()._minimum[X]*2,F->getExtremum()._maximum[X]*2,F->getExtremum()._minimum[Y]*2,F->getExtremum()._maximum[Y]*2,0.1,1000.0);
//    qDebug()<<MP;
    Matrix mvp=MatrixProjection * MatrixView * MatrixModel;
    return mvp;
}

}  // namespace s212
