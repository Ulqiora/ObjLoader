#ifndef SETTINGS_T_H
#define SETTINGS_T_H
#include <QColor>
#include <QFile>

enum class FileType{DEFAULT,CUSTOM};
enum class ProjectionType{PARALLEL,CENTRAL};
enum class EdgesType{SOLID,SHADED};
enum class VerticesShape{NONE,CIRCLE,SQUARE};

struct Settings_t{
    QColor _edgesColor;
    int _edgesThickness;
    EdgesType _edgesType;
    QColor _verticesColor;
    int _verticesSize;
    VerticesShape _verticesShape;
    ProjectionType _projectionType;
    QColor _backColor;
public:
    static Settings_t& instance();
    void initByFileConf(FileType fileId);
private:
    Settings_t();
    Settings_t(const Settings_t& other)=delete;
    Settings_t(const Settings_t&& other)=delete;
};

#endif // SETTINGS_T_H
