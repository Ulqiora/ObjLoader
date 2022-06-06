#ifndef CUSTOMOPENGL_H
#define CUSTOMOPENGL_H
#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollEvent>
#include "../Controller/Controller.h"

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
//                     Shader
private:
    QOpenGLShaderProgram* _IdProgramm=nullptr;
    Matrix MatrixProjection ,MatrixView ,MatrixModel;
    void initShaders();
//                     Facade
private:
    s21::Facade* _facade;
public:
    void setFacade(s21::Facade* facade);
public slots:
    void rotateX(double a);
    void rotateY(double a);
    void rotateZ(double a);
    void moveX(double a);
    void moveY(double a);
    void moveZ(double a);
    void scale(double a);
signals:
    void mouseSignal();
//    OpenGL
public:
    OpenGL(QWidget *parent=nullptr);
    ~OpenGL();
protected:
    void paintGL()override;
    void initializeGL()override;
    void resizeGL(int w,int h)override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent * event) override;
private:
    QPoint _lastPosMouse;
//    signal for settings
public slots:
    void reloadFigure();
};
#endif //  CUSTOMOPENGL_H

