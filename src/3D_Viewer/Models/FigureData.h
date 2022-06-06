#ifndef FIGUREDATA_H
#define FIGUREDATA_H
#include <QFile>
#include <QString>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Manipulations.h"

enum coord{X,Y,Z};

struct Vertex
{
    float _coordinates[3];
};

struct Edge {
    int first;
    int second;
};

struct ExtremumXYZ
{
    float _maximum[3]={0.0,0.0,0.0};
    float _minimum[3]={0.0,0.0,0.0};
    void reset();
};

class FigureData
{
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _indices;
    ExtremumXYZ _extremumValue;
public:
    FigureData(QString objFileName);
    Edge* getIndices();
    Vertex* getVertices();
    unsigned int getSizeVertices();
    unsigned int getSizeIndices();
    ExtremumXYZ& getExtremums();
    ~FigureData()=default;
};

#endif // FIGUREDATA_H
