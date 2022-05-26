#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"
#include <iostream>
typedef struct BoundingBox
{
  // a is bottom left, b is top right.
  bool is_init;
  glm::vec3 a, b;

  BoundingBox()
  : is_init(false)
  {}

  glm::vec3 get_center()
  {
    glm::vec3 ret;
    ret[0] = (b[0] + a[0])/(float)2;
    ret[1] = (b[1] + a[1])/(float)2;
    ret[2] = (b[2] + a[2])/(float)2;
    return ret;
  }
  float get_radius()
  {
    glm::vec3 v = get_center();
    v[0] = a[0] - v[0];
    v[1] = a[1] - v[1];
    v[2] = a[2] - v[2];
    return glm::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  }
  glm::vec3 get_dim()
  {
    glm::vec3 dim;
    dim[0] = glm::abs(a[0]-b[0]);
    dim[1] = glm::abs(a[1]-b[1]);
    dim[2] = glm::abs(a[2]-b[2]);
    return dim;
  }

  void insert_model(const Model& model)
  {
    if (!is_init)
    {
      a[0] = b[0] = model.vertices()[0];
      a[1] = b[1] = model.vertices()[1];
      a[2] = b[2] = model.vertices()[2];
      is_init = true;
    }
    for (int i = 0; i < model.vertices().size(); i+=3)
    {
      if (model.vertices()[i]   < a[0]) a[0] = model.vertices()[i];
      if (model.vertices()[i+1] < a[1]) a[1] = model.vertices()[i+1];
      if (model.vertices()[i+2] < a[2]) a[2] = model.vertices()[i+2];
      if (model.vertices()[i]   > b[0]) b[0] = model.vertices()[i];
      if (model.vertices()[i+1] > b[1]) b[1] = model.vertices()[i+1];
      if (model.vertices()[i+2] > b[2]) b[2] = model.vertices()[i+2];
    }
  }
  
  void insert_model(const std::vector<glm::vec3>& data)
  {
    if (!is_init)
    {
      a = b = data[0];
      is_init = true;
    }
    for (int i = 0; i < data.size(); i+=1)
    {
      if (data[i][0] < a[0]) a[0] = data[i][0];
      if (data[i][1] < a[1]) a[1] = data[i][1];
      if (data[i][2] < a[2]) a[2] = data[i][2];
      if (data[i][0] > b[0]) b[0] = data[i][0];
      if (data[i][1] > b[1]) b[1] = data[i][1];
      if (data[i][2] > b[2]) b[2] = data[i][2];
    }
  }

  void insert_model(glm::vec3* data, const int size)
  {
    if (!is_init)
    {
      a = b = data[0];
      is_init = true;
    }
    for (int i = 0; i < size; i+=1)
    {
      if (data[i][0] < a[0]) a[0] = data[i][0];
      if (data[i][1] < a[1]) a[1] = data[i][1];
      if (data[i][2] < a[2]) a[2] = data[i][2];
      if (data[i][0] > b[0]) b[0] = data[i][0];
      if (data[i][1] > b[1]) b[1] = data[i][1];
      if (data[i][2] > b[2]) b[2] = data[i][2];
    }
  }

  void print_data()
  {
    std::cout << "a = (" << a[0] << ", " << a[1] << ", " << a[2] << ')' << std::endl;
    std::cout << "b = (" << b[0] << ", " << b[1] << ", " << b[2] << ')' << std::endl;
    std::cout << "center = (" << get_center()[0] << ", " << get_center()[1] << ", " << get_center()[2] << ')' << std::endl;
    std::cout << "Radius: " << get_radius() << std::endl;
  }

} BoundingBox;

class BL2GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    BL2GLWidget (QWidget *parent=0);
    ~BL2GLWidget ();

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
    virtual void modelTransform (GLuint VAO);

    virtual void projectTransform();
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

    // Program
    QOpenGLShaderProgram *program;
    // Viewport
    GLint ample, alt;
    // Internal vars
    float escala;
    glm::vec3 pos;
};

