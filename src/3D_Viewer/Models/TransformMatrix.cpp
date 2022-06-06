#include "TransformMatrix.h"
namespace s21 {

//    TransformMatrixBuilder 
//    Значение подавать в радианах
Matrix TransformMatrixBuilder::CreateRotateMatrix(const double& x, const double& y,
                                                           const double& z) {
    Matrix transformMatrix(4,4);
    transformMatrix(0, 0) = cos(y) * cos(z);
    transformMatrix(0, 1) = -cos(y) * sin(z);
    transformMatrix(0, 2) = -sin(y);
    transformMatrix(1, 0) = -sin(x) * sin(y) * cos(z) + cos(x) * sin(z);
    transformMatrix(1, 1) = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
    transformMatrix(1, 2) = -sin(x) * cos(y);
    transformMatrix(2, 0) = cos(x) * sin(y) * cos(z) + sin(x) * sin(z);
    transformMatrix(2, 1) = -cos(x) * sin(y) * sin(z) + sin(x) * cos(z);
    transformMatrix(2, 2) = cos(x) * cos(y);
    transformMatrix(3, 3) = 1.0;
    return transformMatrix;
}

Matrix TransformMatrixBuilder::CreateMoveMatrix(const double& x, const double& y,
                                                           const double& z) {
    Matrix transformMatrix(4,4);
    transformMatrix(0, 0) = 1;
    transformMatrix(1, 1) = 1;
    transformMatrix(2, 2) = 1;
    transformMatrix(3, 3) = 1;
    transformMatrix(0, 3) = x;
    transformMatrix(1, 3) = y;
    transformMatrix(2, 3) = z;
    return transformMatrix;
}

Matrix TransformMatrixBuilder::CreateScaleMatrix(const double& scale) {
    Matrix transformMatrix(4,4);
    transformMatrix(0, 0) = scale;
    transformMatrix(1, 1) = scale;
    transformMatrix(2, 2) = scale;
    transformMatrix(3, 3) = 1;
    return transformMatrix;
}

//    fovy- угол в радианах
Matrix TransformMatrixBuilder::CreatePerspectiveMatrix(const double& fovy, const double& aspect, const double& n, const double& f) {
    Matrix transformMatrix(4,4);
    transformMatrix(0,0)=1/(aspect*std::tan(0.5*fovy));
    transformMatrix(1,1)=1/(std::tan(0.5*fovy));
    transformMatrix(2,2)=-(-n-f)/(n-f);
    transformMatrix(2,3)=2*n*f/(n-f);
    transformMatrix(3,2)=-1;
    return transformMatrix;
}

Matrix TransformMatrixBuilder::CreateOrthoMatrix(ExtremumXYZ v) {
    v._minimum[Z]=0.1;
    v._minimum[Y]*=2;
    v._minimum[X]*=2;
    v._maximum[Y]*=2;
    v._maximum[X]*=2;
    v._maximum[Z]=1000.0;
    Matrix transformMatrix(4,4);
    transformMatrix(0,0)=2/(v._maximum[X]-v._minimum[X]);
    transformMatrix(1,1)=2/(v._maximum[Y]-v._minimum[Y]);
    transformMatrix(2,2)=-2/(v._maximum[Z]-v._minimum[Z]);

    transformMatrix(3,0)=-(v._maximum[X]+v._minimum[X])/(v._maximum[X]-v._minimum[X]);
    transformMatrix(3,1)=-(v._maximum[Y]+v._minimum[Y])/(v._maximum[Y]-v._minimum[Y]);
    transformMatrix(3,2)=-(v._maximum[Z]+v._minimum[Z])/(v._maximum[Z]-v._minimum[Z]);
    transformMatrix(3,3)=1;
    return transformMatrix.transpose();
}

Matrix TransformMatrixBuilder::CreateViewMatrix(){
    Matrix transformMatrix(4,4);
    transformMatrix(0,0)=1;
    transformMatrix(1,1)=1;
    transformMatrix(2,2)=1;
    transformMatrix(3,3)=1;
    transformMatrix = CreateMoveMatrix(0.0,0.0,-3.0) * transformMatrix;
    return transformMatrix;
}

}  // namespace s21
