#include "BL2GLWidget.h"

#include <iostream>

BL2GLWidget::BL2GLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  homer.load("homer.obj");
  homer_deg = 0.0f;
}

BL2GLWidget::~BL2GLWidget ()
{
  if (program != NULL)
    delete program;
}

void BL2GLWidget::ini_camera ()
{
  OBS = glm::vec3(0.0f, 0.0f, 5.0f);
  VRP = glm::vec3(0.0f, 0.0f, 0.0f);
  up =  glm::vec3(0.0f, 1.0f, 0.0f);

  FOV = float(M_PI)/2.0f;
  ra = 1.0f;
  znear = 0.4f;
  zfar = 20.0f;



  projectTransform();
  viewTransform();
}

void BL2GLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  escala = 1.0f;

  ini_camera();

  glEnable(GL_DEPTH_TEST); 
}

void BL2GLWidget::projectTransform()
{
  glm::mat4 PM;
  PM = glm::perspective(FOV, ra, znear, zfar);
  glUniformMatrix4fv(PMLoc, 1, GL_FALSE, &PM[0][0]);
}

void BL2GLWidget::viewTransform()
{
  glm::mat4 VM;
  VM = glm::lookAt(OBS, VRP, up);
  glUniformMatrix4fv(VMLoc, 1, GL_FALSE, &VM[0][0]);
}

void BL2GLWidget::paintGL () 
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform();
  
  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAO_Homer);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, homer.faces().size()*3);

  glBindVertexArray (0);
}

void BL2GLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala));
  transform = glm::rotate(transform, homer_deg, glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void BL2GLWidget::resizeGL (int w, int h) 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void BL2GLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    case Qt::Key_R:
      homer_deg += float(M_PI)/4.0f;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void BL2GLWidget::creaBuffers () 
{
  // Dades de la caseta
  // Dos VBOs, un amb posició i l'altre amb color

  
  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  // Homer es todo triangulos, cada triangulo tiene 3 vértices con 3 floats -> 9 floats, 
  glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float)*homer.faces().size(), homer.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, false
                        , 3*sizeof(float) // Tenemos que cada triplete de coords son 3 floats. 
                        , 0);
  glEnableVertexAttribArray(vertexLoc); 

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float)*homer.faces().size(), homer.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, false
                        , 3*sizeof(float) // Tenemos que cada triplete de color son 3 floats. 
                        , 0);
  glEnableVertexAttribArray(colorLoc);          

  glBindVertexArray (0);
}

void BL2GLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  PMLoc = glGetUniformLocation(program->programId(), "PM");
  VMLoc = glGetUniformLocation(program->programId(), "VM");
}

