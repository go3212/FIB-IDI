TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += .

FORMS += MyForm.ui

HEADERS += MyForm.h BL3GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        BL3GLWidget.cpp MyGLWidget.cpp model.cpp
