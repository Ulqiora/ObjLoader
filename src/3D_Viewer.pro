QT += core gui

LIBS+= -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ../src/3D_Viewer/Models/Figure.cpp\
    ../src/3D_Viewer/Models/Matrix.cpp\
    ../src/3D_Viewer/Models/TransformMatrix.cpp\
    ../src/3D_Viewer/Controller/Controller.cpp \
    ../src/3D_Viewer/CustomWidget/CustomOpenGL.cpp \
    ../src/3D_Viewer/main.cpp \
    ../src/3D_Viewer/View/ViewApplication.cpp \
    ../src/3D_Viewer/View/SettingsView.cpp \
    3D_Viewer/Models/FigureData.cpp \
    3D_Viewer/Models/Settings_t.cpp

HEADERS += \
    ../src/3D_Viewer/Models/Figure.h\
    ../src/3D_Viewer/Models/Matrix.h\
    ../src/3D_Viewer/Models/TransformMatrix.h\
    ../src/3D_Viewer/Controller/Controller.h \
    ../src/3D_Viewer/CustomWidget/CustomOpenGL.h \
    ../src/3D_Viewer/View/ViewApplication.h \
    ../src/3D_Viewer/View/SettingsView.h \
    3D_Viewer/Models/Manipulations.h \
    3D_Viewer/Models/Settings_t.h \
 \#    ../src/3D_Viewer/Models/Vertex.h
    3D_Viewer/Models/FigureData.h

FORMS += \
    ../src/3D_Viewer/UI_Files/ViewApplication.ui \
    ../src/3D_Viewer/UI_Files/SettingsView.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../src/3D_Viewer/Resources/resources1.qrc

