######################################################################
# Automatically generated by qmake (3.0) ? 11 16 11:54:38 2013
######################################################################

QT += core gui opengl

TEMPLATE = app
TARGET = qtsample_04
INCLUDEPATH += .\
                src\
                C:/lib/glew/include\
                C:/lib/glm
LIBS += -LC:/lib/glew/lib\
        -lopengl32\
        -lglew32


# Input
HEADERS += src/Tetrahedron.h\
           src/GLSLProgram.h\

SOURCES += src/main.cpp\
           src/Tetrahedron.cpp\
           src/GLSLProgram.cpp\