#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    MyGLWidget (QWidget* parent = 0);
    ~MyGLWidget();
    
protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    void createBuffers();
    void loadShaders();

    unsigned int vertexLoc;
    QOpenGLShaderProgram* program;

    unsigned int VAO1;

};