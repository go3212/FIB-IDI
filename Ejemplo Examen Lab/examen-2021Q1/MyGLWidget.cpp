// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() 
{
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  //ExamGLWidget::paintGL();
  viewTransform();
  projectTransform();

  emit changedCube(patr_cub);
  emit changedPerspectiveCamera(camPlanta);

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // VAO Cubo
  if (cubes_visible)
  {
    glBindVertexArray(VAO_Cub);
    //    Cubo 1
    MyGLWidget::modelTransformCub(2.0f, glm::radians(0.0f   + 120.0f*cube_offset));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //    Cubo 2
    MyGLWidget::modelTransformCub(2.5f, glm::radians(120.0f + 120.0f*cube_offset));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    MyGLWidget::modelTransformCub(3.0f, glm::radians(240.0f + 120.0f*cube_offset));
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  else 
  {
    // VAO Patricio
    glBindVertexArray(VAO_Patr);
    MyGLWidget::modelTransformPatricio(patr_cub);
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }


}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  // ExamGLWidget::modelTransformCub (1.0, 0.0);
  // En aquest mètode has de substituir aquest codi per construir la 
  // transformació geomètrica (TG) del cub usant els paràmetres adientment
  // El tamaño por defecto del cubo es 0.5 por lado.
  TG = glm::mat4(1.0f);
  TG = glm::rotate(TG, angle, glm::vec3(0.0f, 1.0f, 0.0f));
  TG = glm::translate(TG, glm::vec3(5.0f, 0.0f, 0.0f));
  TG = glm::scale(TG, escala*2.0f*glm::vec3(1.0f, 1.0f, 1.0f)); // Escala 1.
  // El cubo está centrado.
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio (int cub)    // Mètode que has de modificar
{
  //ExamGLWidget::modelTransformPatricio ();
  float angle = 120.0f*cube_offset;
  if (cub == 1) angle += 0.0f;
  if (cub == 2) angle += 120.0f;
  if (cub == 3) angle += 240.0f;
  TG = glm::mat4(1.0f);
  TG = glm::rotate(TG, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
  TG = glm::translate(TG, glm::vec3(5.0f, 0.0f, 1.0f));
  TG = glm::rotate(TG, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  TG = glm::scale(TG, 2.0f*escala*glm::vec3(1.0f, 1.0f, 1.0f));
  TG = glm::translate(TG, -centreBasePat);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 10.0f, 0.0f) + centreEsc, centreEsc, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 proj;
    proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
  }
}

void send_light()
{
  
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      cubes_visible = !cubes_visible;
    break;
	}
  case Qt::Key_1: {
      patr_cub = 1;
    break;
	}
  case Qt::Key_2: {
      patr_cub = 2;
    break;
	}
  case Qt::Key_3: {
      patr_cub = 3;
    break;
	}
  case Qt::Key_F: {
      light_yellow = !light_yellow;
      glm::vec3 light = glm::vec3(1.0f, 1.0f, 1.0f);
      if (light_yellow) light = glm::vec3(1.0f, 1.0f, 0.0f);
      glUniform3fv(colfocusLoc, 1, &light[0]);
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
    break;
	}
  case Qt::Key_Right: {
      cube_offset = (cube_offset + 1)%3;
      
    break;
	}
  case Qt::Key_Left: {
      cube_offset = (cube_offset - 1)%3;
    break;
	}
  case Qt::Key_R: {
      cube_offset = 0;
      camPlanta = false;
      patr_cub = 1;
      cubes_visible = true;

      light_yellow = false;
      glm::vec3 light = glm::vec3(1.0f, 1.0f, 1.0f);
      glUniform3fv(colfocusLoc, 1, &light[0]);
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

