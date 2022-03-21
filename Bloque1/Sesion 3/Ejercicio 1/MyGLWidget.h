#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    virtual void modelTransform();

    virtual void keyPressEvent(QKeyEvent *e);

private:
    void createBuffers();
    void loadShaders();

    unsigned int vertexLoc;
    unsigned int vertexColor;
    unsigned int screenSize;
    QOpenGLShaderProgram* program;

    float scl;
    unsigned int sclLoc;

    glm::mat4 TG;
    unsigned int TGLoc;

    glm::vec3 transVec;


    unsigned int VAO1;

};