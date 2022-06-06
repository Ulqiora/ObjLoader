#include "Figure.h"

Figure::Figure()
{

}

void Figure::initByObjFile(QString fileName){
    if  (_data!=nullptr) {
        delete _data;
        _data=nullptr;
    }
    _data=new FigureData(fileName);
//    qDebug()<<_data->getExtremums()._maximum[X];
//    qDebug()<<_data->getExtremums()._maximum[Y];
//    qDebug()<<_data->getExtremums()._maximum[Z];
//    qDebug()<<_data->getExtremums()._minimum[X];
//    qDebug()<<_data->getExtremums()._minimum[Y];
//    qDebug()<<_data->getExtremums()._minimum[Z];
}

FigureData* Figure::getData(){
    return _data;
}

ExtremumXYZ Figure::getExtremum(){
    return _data->getExtremums();
}
Manipulations Figure::getManipulation(){
    return _edited;
}
void Figure::setRotateX(float value){
    _edited._rotate[X]=value;
}
void Figure::setRotateY(float value){
    _edited._rotate[Y]=value;
}
void Figure::setRotateZ(float value){
    _edited._rotate[Z]=value;
}
void Figure::setMoveX(float value){
    _edited._move[X]=value;
}
void Figure::setMoveY(float value){
    _edited._move[Y]=value;
}
void Figure::setMoveZ(float value){
    _edited._move[Z]=value;
}
void Figure::setScale(float value){
    _edited._scale=value;
}

Figure::~Figure(){
    delete _data;
    _data=nullptr;
}
