######################################################################
# Automatically generated by qmake (3.0) ? 5 10 16:58:07 2014
######################################################################

TEMPLATE = app
QT += core gui widgets opengl
greaterThan(QT_MAJOR_VERSION, 4)

TARGET = sample_qglwidget
INCLUDEPATH += .\
               src\
               C:/lib/glm\
               C:/lib/glew/include\

LIBS +=  \

QMAKE_CXXFLAGS += -std=c++11 -O0

# Input
RESOURCES = resources.qrc
HEADERS += \
           src/MainWindow.h\
           src/util/util.hpp\
           src/util/ShaderProgram.h\
           src/GLViewer.h\
           src/model/Model1.h\
           src/model/Model2.h\
           src/model/Model3.h\
           src/model/Model4.h\
           src/model/Model5.h\
           
SOURCES += src/main.cpp\
           src/MainWindow.cpp\
           src/util/ShaderProgram.cpp\
           src/GLViewer.cpp\
           src/model/Model1.cpp\
           src/model/Model2.cpp\
           src/model/Model3.cpp\
           src/model/Model4.cpp\
           src/model/Model5.cpp\

# Directories
