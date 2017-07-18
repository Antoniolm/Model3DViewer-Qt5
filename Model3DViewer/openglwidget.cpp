// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "openglwidget.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QExposeEvent>
#include "vertex.h"

// Create a colored cube
static const QVector3D sg_vertexes[] = {
    // Face 1 (Front)
      QVector3D( 0.5f,  0.5f,  0.5f),
      QVector3D(-0.5f,  0.5f,  0.5f),
      QVector3D(-0.5f, -0.5f,  0.5f),
      QVector3D(-0.5f, -0.5f,  0.5f),
      QVector3D( 0.5f, -0.5f,  0.5f),
      QVector3D( 0.5f,  0.5f,  0.5f),
    // Face 2 (Back)
      QVector3D( 0.5f, -0.5f, -0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D( 0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D( 0.5f, -0.5f, -0.5f),
      QVector3D(-0.5f, -0.5f, -0.5f),
    // Face 3 (Top)
      QVector3D( 0.5f,  0.5f,  0.5f),
      QVector3D( 0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f,  0.5f,  0.5f),
      QVector3D( 0.5f,  0.5f,  0.5f),
    // Face 4 (Bottom)
      QVector3D( 0.5f, -0.5f,  0.5f),
      QVector3D(-0.5f, -0.5f,  0.5f),
      QVector3D(-0.5f, -0.5f, -0.5f),
      QVector3D(-0.5f, -0.5f, -0.5f),
      QVector3D( 0.5f, -0.5f, -0.5f),
      QVector3D( 0.5f, -0.5f,  0.5f),
    // Face 5 (Left)
      QVector3D(-0.5f, -0.5f,  0.5f),
      QVector3D(-0.5f,  0.5f,  0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f, -0.5f,  0.5f),
      QVector3D(-0.5f,  0.5f, -0.5f),
      QVector3D(-0.5f, -0.5f, -0.5f),
    // Face 6 (Right)
      QVector3D( 0.5f,  0.5f,  0.5f),
      QVector3D( 0.5f, -0.5f,  0.5f),
      QVector3D( 0.5f, -0.5f, -0.5f),
      QVector3D( 0.5f, -0.5f, -0.5f),
      QVector3D( 0.5f,  0.5f, -0.5f),
      QVector3D( 0.5f,  0.5f,  0.5f)
};

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent){
    camera=new Camera();
    camera->setCamera(QVector3D(0.0f,0.0f,-2.5f),QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));
    camera->setPerspective(45.0f, 400 / float(800), 0.0f, 1000.0f);
}

//**********************************************************************//

OpenGLWidget::~OpenGLWidget(){
    // Actually destroy our OpenGL information
    object.destroy();
    vertex.destroy();
    delete program;
    delete camera;
}

//**********************************************************************//

void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();

    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Compile of build of a shader program
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/simple.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    program->link();
    program->bind();

    //Create our buffer of vertex
    vertex.create();
    vertex.bind();
    vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

    //Create our object 3D
    object.create();
    object.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, sizeof(sg_vertexes), 3, sizeof(QVector3D));

    //Release opengl information
    object.release();
    vertex.release();
    program->release();
}

//**********************************************************************//

void OpenGLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    program->bind();
    program->setUniformValue(program->uniformLocation("projection"), projection);
    //camera->activate(program);
    object.bind();
    update();
    QMatrix4x4 transform;
    transform.translate(0.0f,0.0f,-2.5f);

    program->setUniformValue(program->uniformLocation("view"), transform);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    object.release();
    program->release();
}

//**********************************************************************//

void OpenGLWidget::resizeGL(int w, int h){
    projection.setToIdentity();
    projection.perspective(45.0f, w / float(h), 0.0f, 1000.0f);
}

//**********************************************************************//

void OpenGLWidget::update()
{
  QOpenGLWidget::update();
}
