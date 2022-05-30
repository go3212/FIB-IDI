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
  std::vector<glm::vec3> vertexs;

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

  void move(glm::vec3 vec_move)
  {
    for (auto& vertex : vertexs)
    {
      vertex[0] += vec_move[0];
      vertex[1] += vec_move[1];
      vertex[2] += vec_move[2];
    }
    a += vec_move;
    b += vec_move;
  }

  glm::vec3* get_vertexs()
  {
    return &vertexs[0];
  }

  size_t get_vertexs_size()
  {
    return vertexs.size()*sizeof(glm::vec3);
  }

  glm::vec3 get_base_center()
  {
    glm::vec3 ret;
    ret[0] = (b[0] + a[0])/(float)2;
    ret[1] = a[1];
    ret[2] = (b[2] + a[2])/(float)2;
    return ret;
  } 

  void insert_model(Model& model)
  {
    for (int i = 0; i < 9*model.faces().size(); i+=3)
      vertexs.push_back(glm::vec3((float)model.VBO_vertices()[i], 
                                  (float)model.VBO_vertices()[i+1], 
                                  (float)model.VBO_vertices()[i+2]));
    calculate_bounding();
  }
  
  void uniform_set_height(float scale)
  {
    glm::vec3 base = get_base_center();
    float h = b[1] - a[1];
    for (auto& vertex : vertexs)
      vertex = vertex*scale/h + base;
    calculate_bounding();
  }

  void insert_model(const std::vector<glm::vec3>& data)
  {
    for (int i = 0; i < data.size(); i+=1) vertexs.push_back(data[i]);
    calculate_bounding();
  }

  void insert_model(glm::vec3* data, const int size)
  {
    for (int i = 0; i < size; i+=1) vertexs.push_back(data[i]);
    calculate_bounding();
  }

  void insert_model(float* data, const int size)
  {
    for (int i = 0; i < size; i+=3) vertexs.push_back(glm::vec3(data[i], data[i+1], data[i+2]));
    calculate_bounding();
  }

  void calculate_bounding()
  {
    a = b = vertexs[0];
    for (size_t i = 0; i < vertexs.size(); ++i)
    {
      if (vertexs[i][0] < a[0]) a[0] = vertexs[i][0];
      if (vertexs[i][1] < a[1]) a[1] = vertexs[i][1];
      if (vertexs[i][2] < a[2]) a[2] = vertexs[i][2];
      if (vertexs[i][0] > b[0]) b[0] = vertexs[i][0];
      if (vertexs[i][1] > b[1]) b[1] = vertexs[i][1];
      if (vertexs[i][2] > b[2]) b[2] = vertexs[i][2];
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
    virtual void mouseMoveEvent(QMouseEvent* event);
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

