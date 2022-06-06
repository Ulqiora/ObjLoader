#include "Settings_t.h"
Settings_t::Settings_t(){

}
Settings_t& Settings_t::instance(){
    static Settings_t single;
    single.initByFileConf(FileType::CUSTOM);
    return single;
}

void Settings_t::initByFileConf(FileType fileId){
    QString fname;
    if (fileId == FileType::DEFAULT) {
        fname = ":/settings/SettingsConf/setting_default.conf";
    } else if (fileId == FileType::CUSTOM) {
        fname = "./setting_current.conf";
    }
    QFile file(fname);
    file.open(QFile::ReadOnly | QFile::Text);
      std::string buf;
      size_t count = 0;
      while (!file.atEnd()) {
          buf = file.readLine().toStdString();
          if (count == 0) {
              buf[buf.size() - 1] = '\0';
              _edgesColor.setNamedColor(buf.c_str());
          } else if (count == 1) {
              sscanf(buf.c_str(), "%d", &_edgesThickness);
          } else if (count == 2) {
              if (!buf.compare("0\n")) {
                  _edgesType = EdgesType::SOLID;
              } else if (!buf.compare("1\n")) {
                  _edgesType = EdgesType::SHADED;
              }
          } else if (count == 3) {
              buf[buf.size() - 1] = '\0';
              _verticesColor.setNamedColor(buf.c_str());
          } else if (count == 4) {
              sscanf(buf.c_str(), "%d", &_verticesSize);
          } else if (count == 5) {
              if (!buf.compare("0\n")) {
                  _verticesShape = VerticesShape::NONE;
              } else if (!buf.compare("1\n")) {
                  _verticesShape = VerticesShape::CIRCLE;
              } else if (!buf.compare("2\n")) {
                  _verticesShape = VerticesShape::SQUARE;
              }
          } else if (count == 6) {
              if (!buf.compare("0\n")) {
                  _projectionType = ProjectionType::PARALLEL;
              } else if (!buf.compare("1\n")) {
                  _projectionType = ProjectionType::CENTRAL;
              }
          } else if (count == 7) {
              buf[buf.size() - 1] = '\0';
              _backColor.setNamedColor(buf.c_str());
          }
          count++;
      }
      file.close();
}
