#include "View/ViewApplication.h"
#include "CustomWidget/CustomOpenGL.h"
#include "View/SettingsView.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings_t& _settingsInfo=Settings_t::instance();
    SettingsView settings(&_settingsInfo);
    Figure figure;
    s21::Facade facade(&figure,&_settingsInfo);
    ViewApplication w(&settings,&facade);
    w.show();
    return a.exec();
}
