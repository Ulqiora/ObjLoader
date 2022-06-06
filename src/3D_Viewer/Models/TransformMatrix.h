#pragma once
#include <cmath>
#include <iostream>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include "Matrix.h"
#include "FigureData.h"
const double MATH_PI = acos(-1);
namespace s21 {

class TransformMatrixBuilder {
   public:
    static Matrix CreateRotateMatrix(const double& x, const double& y, const double& z);
    static Matrix CreateMoveMatrix(const double& x, const double& y, const double& z);
    static Matrix CreateScaleMatrix(const double& scale);
    static Matrix CreatePerspectiveMatrix(const double& fovy, const double& aspect, const double& n, const double& f);
    static Matrix CreateOrthoMatrix(ExtremumXYZ extremum);
    static Matrix CreateViewMatrix();
};

}  // namespace s21

