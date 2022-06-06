#pragma once
#include "../Models/Figure.h"
#include "../Models/Settings_t.h"
#include "../Models/TransformMatrix.h"
namespace s21 {

class Facade {
 private:
    Figure* F;
    Settings_t* _settings;
 public:
    Facade(Figure *Single, Settings_t* settings) : F(Single), _settings(settings){}
    ~Facade() {}
    Figure* getFigure();
    Settings_t* getSettings();
    Matrix getMvpMatrix();
    void updateModel(QString file_name);
};

}  // namespace s212
