#include "MyGLWidget.h"

#include <iostream>


MyGLWidget::MyGLWidget (QWidget* parent) 
	: QOpenGLWidget(parent)
	, program(nullptr)
	, scl(0.5f)
	, transVec(0.0f, 0.0f, 0.0f)
{
	setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
	if (program != nullptr)
	delete program;
}

void MyGLWidget::initializeGL ()
{
	// Cal inicialitzar l'ús de les funcions d'OpenGL
	initializeOpenGLFunctions();
	
	glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
	loadShaders();
	createBuffers();
}

void MyGLWidget::paintGL ()
{
	glClear(GL_COLOR_BUFFER_BIT);

	modelTransform();
	glBindVertexArray(VAO1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
	// Aquí anirà el codi que cal fer quan es redimensiona la finestra
}

void MyGLWidget::createBuffers ()
{
	glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
	Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
	Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
	Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
	
	// Creació del Vertex Array Object (VAO) que usarem per pintar
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	// Creació del buffer amb les dades dels vèrtexs
	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	// Activem l'atribut que farem servir per vèrtex	
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLoc);

	glm::vec4 color[4];
	color[0] = glm::vec4(1.0, 0.0, 0.0, 1.0); 
	color[1] = glm::vec4(1.0, 0.0, 0.0, 1.0); 
	color[2] = glm::vec4(0.0, 1.0, 0.0, 1.0); 

	unsigned int vbo2;
	
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexColor);

	// Desactivem el VAO
	glBindVertexArray(0);
}

void MyGLWidget::loadShaders()
{
	// Creem els shaders per al fragment shader i el vertex shader
	QOpenGLShader fs (QOpenGLShader::Fragment, this);
	QOpenGLShader vs (QOpenGLShader::Vertex, this);
	// Carreguem el codi dels fitxers i els compilem
	fs.compileSourceFile("./shaders/fragshad.frag");
	vs.compileSourceFile("./shaders/vertshad.vert");
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
	vertexColor = glGetAttribLocation (program->programId(), "in_color");
	screenSize = glGetUniformLocation (program->programId(), "screenSize");
	glUniform2f(screenSize, width(), height());
	sclLoc = glGetUniformLocation(program->programId(), "scl");
	glUniform1f(sclLoc, scl);
	TGLoc = glGetUniformLocation(program->programId(), "TG");

}

void MyGLWidget::modelTransform()
{
	glm::mat4 TG (1.0);
	TG = glm::translate(TG, transVec);
	TG = glm::scale(TG, glm::vec3(scl, scl, scl));
	

	glUniformMatrix4fv(TGLoc, 1, false, &TG[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e)
{
	makeCurrent();
	switch(e->key())
	{
		case Qt::Key_S:
			scl += 0.1f;
			glUniform1f(sclLoc, scl);
			break;
		case Qt::Key_D:
			scl -= 0.1f;
			glUniform1f(sclLoc, scl);
			break;	
		case Qt::Key_Right:
			transVec[0] += 0.1f;
			break;
		case Qt::Key_Left:
			transVec[0] -= 0.1f;
			break;
		case Qt::Key_Up:
			transVec[1] += 0.1f;
			break;
		case Qt::Key_Down:
			transVec[1] -= 0.1f;
			break;
		default: e->ignore();
	}
	update();
}