#include "FigureData.h"

FigureData::FigureData(QString objFileName)
{
    _extremumValue.reset();
    _vertices.resize(0);
    _indices.resize(0);
    std::ifstream obj(objFileName.toStdString());
    std::string currentLine="", prefix="";
    std::stringstream ss;
    Vertex point;
    Edge edge;
    if (!obj.is_open()) {
        throw std::invalid_argument("ERROR::OBJLOADER::Could not open file.");
    }
    while (std::getline(obj, currentLine)) {
        //Get the prefix of the line
        ss.clear(), ss.str(currentLine), ss >> prefix;
        if (prefix=="v") {
            ss >> point._coordinates[X] >> point._coordinates[Y] >> point._coordinates[Z];
            _extremumValue._maximum[X]=std::max(_extremumValue._maximum[X],point._coordinates[X]);
            _extremumValue._maximum[Y]=std::max(_extremumValue._maximum[Y],point._coordinates[Y]);
            _extremumValue._maximum[Z]=std::max(_extremumValue._maximum[Z],point._coordinates[Z]);
            _extremumValue._minimum[X]=std::min(_extremumValue._minimum[X],point._coordinates[X]);
            _extremumValue._minimum[Y]=std::min(_extremumValue._minimum[Y],point._coordinates[Y]);
            _extremumValue._minimum[Z]=std::min(_extremumValue._minimum[Z],point._coordinates[Z]);
            _vertices.push_back(point);
        } else if (prefix=="f") {
            int counter = 0,temp=0;
            int firstIndexofPolygon=0;
            int numIndexOfPolygon=0;
            while (ss >> temp) {
                temp--;
                if (counter == 0){
                    if(numIndexOfPolygon==0){
                        firstIndexofPolygon=temp;
                    } else if (numIndexOfPolygon==1) {
                        edge={firstIndexofPolygon,temp};
                        _indices.push_back(edge);
                    } else {
                        edge={_indices.back().second,temp};
                        _indices.push_back(edge);
                    }
                    numIndexOfPolygon++;
                }
                //Handling characters
                if (ss.peek() == '/') {
                    ss.ignore(1, '/');
                    counter++;
                    if(ss.peek() == '/'){
                        ss.ignore(1, '/');
                        counter++;
                    }
                } else if (ss.peek() == ' ') {
                    ss.ignore(1, ' ');
                    counter=0;
                }
                //Reset the counter
                if (counter > 2) counter = 0;
            }
            edge={_indices.back().second,firstIndexofPolygon};
            _indices.push_back(edge);
        }
    }
}

Edge* FigureData::getIndices(){
    return &(_indices[0]);
}
Vertex* FigureData::getVertices(){
    return &(_vertices[0]);
}
unsigned int FigureData::getSizeVertices(){
    return _vertices.size();
}
unsigned int FigureData::getSizeIndices(){
    return _indices.size();
}

ExtremumXYZ& FigureData::getExtremums(){
    return _extremumValue;
}

void ExtremumXYZ::reset()
{
    _minimum[X]=_minimum[Y]=_minimum[Z]=1.0/0.0;
    _maximum[X]=_maximum[Y]=_maximum[Z]=-1.0/0.0;
}

