#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"
#include "boundingbox.h"
#include <iostream>

class BL2GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    BL2GLWidget (QWidget *parent=0);
    ~BL2GLWidget ();

  public Q_SLOTS:
    void setFOV(int zoom)
    {
      makeCurrent();
      this->zoom = 1.0f;
      this->zoom -= (float)zoom/100.0f;
      ini_camera();
      update();
    }
         Q_SIGNALS:
    void valueChangedFOV(int fov);


  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void modelTransform (GLuint VAO);

    virtual void projectTransform();
    virtual void patTransform(glm::vec3 pos, glm::vec3 looking);
    virtual void viewTransform();
    virtual void ini_camera ();

    virtual void creaBuffers ();
    virtual void carregaShaders ();

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar;

    // Bounding BOx
    BoundingBox* boundingbox;

    // attribute locations
    GLuint vertexLoc, colorLoc;
    // uniform locations
    GLuint transLoc, PMLoc, VMLoc;
    // VAO i VBO names
    Model homer; 
    GLuint VAO_Homer;
    GLuint VBO_Homer[2];
    float homer_deg;

    GLuint VAO_suelo;
    GLuint VBO_suelo[2];

    // ANGLES
    float phi, theta, psi; // X Y Z 
    float x_prev, y_prev;

    // ZOOM
    float zoom;

    // Program
    QOpenGLShaderProgram *program;
    // Viewport
    GLint ample, alt;
    // Internal vars
    float escala;
    glm::vec3 pos;
};

