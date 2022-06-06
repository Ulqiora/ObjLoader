#ifndef FIGURE_H
#define FIGURE_H
#include "FigureData.h"

#include "Manipulations.h"
#include <vector>
#include <string>
#include <QString>
#include <QFile>
#include <QDebug>
class Figure
{
private:
    FigureData* _data=nullptr;
    Manipulations _edited;
public:
    Figure();
    void initByObjFile(QString fileName);
    FigureData* getData();
    ExtremumXYZ getExtremum();
    Manipulations getManipulation();
    void setRotateX(float value);
    void setRotateY(float value);
    void setRotateZ(float value);
    void setMoveX(float value);
    void setMoveY(float value);
    void setMoveZ(float value);
    void setScale(float value);
    ~Figure();
};

#endif // FIGURE_H
