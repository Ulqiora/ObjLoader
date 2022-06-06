#include "CustomOpenGL.h"

OpenGL::OpenGL(QWidget *parent):QOpenGLWidget(parent){
}

void OpenGL::setFacade(s21::Facade* facade){
    _facade=facade;
}

OpenGL::~OpenGL(){
    if(_IdProgramm==nullptr)
        return;
    makeCurrent();
    delete _IdProgramm;
    _IdProgramm=nullptr;
    doneCurrent();
}

void OpenGL::initShaders(){
    if(!_IdProgramm->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/Shaders/vertex_shader.glsl"))
        close();
    if (!_IdProgramm->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/Shaders/fragment_shader.glsl"))
        close();
    if(!_IdProgramm->link())
        close();
    if(!_IdProgramm->bind())
        close();
}

void OpenGL::initializeGL(){
    initializeOpenGLFunctions();
    _IdProgramm=new  QOpenGLShaderProgram();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShaders();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
}

void OpenGL::paintGL(){
    glClearColor(_facade->getSettings()->_backColor.redF(),_facade->getSettings()->_backColor.greenF(),_facade->getSettings()->_backColor.blueF(),_facade->getSettings()->_backColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    if(_facade->getFigure()->getData()!=nullptr){
        QOpenGLVertexArrayObject VAO;
        QOpenGLBuffer VBO(QOpenGLBuffer::VertexBuffer), EBO(QOpenGLBuffer::IndexBuffer);
        VAO.create(),VBO.create(),EBO.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
        _facade->getFigure()->getData()->getIndices();
        _facade->getFigure()->getData()->getSizeIndices();
        VBO.bind() , VBO.allocate(_facade->getFigure()->getData()->getVertices(),_facade->getFigure()->getData()->getSizeVertices()*sizeof(Vertex));
        EBO.bind() , EBO.allocate(_facade->getFigure()->getData()->getIndices(),_facade->getFigure()->getData()->getSizeIndices()*sizeof(Edge));
        Matrix MVP=_facade->getMvpMatrix();
        QMatrix4x4 Q_MVP(MVP.getMass(),4,4);

        glVertexAttribPointer( glGetAttribLocation(_IdProgramm->programId(),"coord3d") , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        _IdProgramm->bind();
        _IdProgramm->setUniformValue(_IdProgramm->uniformLocation("MVP_Matrix"), Q_MVP);
        float edgesColor[4]={_facade->getSettings()->_edgesColor.redF(),_facade->getSettings()->_edgesColor.greenF(),_facade->getSettings()->_edgesColor.blueF(),_facade->getSettings()->_edgesColor.alphaF()};
        _IdProgramm->setUniformValueArray(_IdProgramm->uniformLocation("color"),edgesColor,1,4);
        glEnableVertexAttribArray(0);
        if(_facade->getSettings()->_edgesType==EdgesType::SHADED){
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x0101);
        }
        glLineWidth(_facade->getSettings()->_edgesThickness);
        glDrawElements(GL_LINES, (_facade->getFigure()->getData()->getSizeIndices())*2, GL_UNSIGNED_INT, 0);
        _IdProgramm->release();
        if(_facade->getSettings()->_edgesType==EdgesType::SHADED) glDisable(GL_LINE_STIPPLE);

        if(_facade->getSettings()->_verticesShape!=VerticesShape::NONE){
            glVertexAttribPointer( glGetAttribLocation(_IdProgramm->programId(),"coord3d") , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            _IdProgramm->bind();
            _IdProgramm->setUniformValue(_IdProgramm->uniformLocation("MVP_Matrix"), Q_MVP);
            float verticesColor[4]={_facade->getSettings()->_verticesColor.redF(),_facade->getSettings()->_verticesColor.greenF(),_facade->getSettings()->_verticesColor.blueF(),_facade->getSettings()->_verticesColor.alphaF()};
            _IdProgramm->setUniformValueArray(_IdProgramm->uniformLocation("color"),verticesColor,1,4);
            glEnableVertexAttribArray(0);
            if(_facade->getSettings()->_verticesShape==VerticesShape::CIRCLE) glEnable(GL_POINT_SMOOTH);
            glPointSize(_facade->getSettings()->_verticesSize);
            glDrawArrays(GL_POINTS, 0,_facade->getFigure()->getData()->getSizeVertices());
            _IdProgramm->release();
            if(_facade->getSettings()->_verticesShape==VerticesShape::CIRCLE) glDisable(GL_POINT_SMOOTH);
        }
    }
}

void OpenGL::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void OpenGL::rotateX(double value)
{
    _facade->getFigure()->setRotateX(value);
    update();
}

void OpenGL::rotateY(double value)
{
    _facade->getFigure()->setRotateY(value);
    update();
}

void OpenGL::rotateZ(double value)
{
    _facade->getFigure()->setRotateZ(value);
    update();
}

void OpenGL::moveX(double value)
{
    _facade->getFigure()->setMoveX(value);
    update();
}

void OpenGL::moveY(double value)
{
    _facade->getFigure()->setMoveY(value);
    update();
}

void OpenGL::moveZ(double value)
{
    _facade->getFigure()->setMoveZ(value);
    update();
}

void OpenGL::scale(double value)
{
    _facade->getFigure()->setScale(value);
    update();
}

void OpenGL::reloadFigure(){
    this->update();
}

void OpenGL::mousePressEvent(QMouseEvent *event) {
    _lastPosMouse = event->position().toPoint();
}
void OpenGL::mouseMoveEvent(QMouseEvent *event){
    int dx = event->position().toPoint().x() - _lastPosMouse.x();
    int dy = event->position().toPoint().y() - _lastPosMouse.y();

    if (event->buttons() & Qt::RightButton) {
        rotateX(_facade->getFigure()->getManipulation()._rotate[X]+ dy/10.0);
        rotateY(_facade->getFigure()->getManipulation()._rotate[Y] - dx/10.0);
        emit mouseSignal();
    } else if (event->buttons() & Qt::LeftButton) {
        moveX(_facade->getFigure()->getManipulation()._move[X] + pow(_facade->getFigure()->getExtremum()._maximum[Z]-_facade->getFigure()->getExtremum()._minimum[Z],1.7)*dx*_facade->getFigure()->getManipulation()._scale/10000);
        moveY(_facade->getFigure()->getManipulation()._move[Y] - pow(_facade->getFigure()->getExtremum()._maximum[Z]-_facade->getFigure()->getExtremum()._minimum[Z],1.7)*dy*_facade->getFigure()->getManipulation()._scale/10000);
//        emit mouseMoveX(static_cast<int>(positionMove.x()*100));
        emit mouseSignal();
    }
    _lastPosMouse = event->position().toPoint();
    this->update();
}
void OpenGL::wheelEvent(QWheelEvent * event) {
    double dscale=event->angleDelta().y();
    double factor = 1.1;
    if(dscale<0) factor=1/factor;
    scale(_facade->getFigure()->getManipulation()._scale*factor);
    reloadFigure();
    emit mouseSignal();
}
