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

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent){
    mesh=new Mesh(":/chair.obj");

    camera=new Camera();
    camera->setCamera(QVector3D(0.0f,0.0f,-2.5f),QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));
    mouseY=0.0;
    mouseX=0.0;
}

//**********************************************************************//

OpenGLWidget::~OpenGLWidget(){
    // Actually destroy our OpenGL information
    delete program;
    delete camera;
    delete mesh;
}

//**********************************************************************//

void OpenGLWidget::initializeGL(){
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    /*connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(~OGLWidget()), Qt::DirectConnection);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    printVersionInformation();*/

    // Set global information
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Application-specific initialization
    // Create Shader (Do not release until VAO is created)
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/simple.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    program->link();
    program->bind();

    mesh->initialize(program);
}

//**********************************************************************//

void OpenGLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    camera->activate(program);
    update();

    mesh->visualization();
}

//**********************************************************************//

void OpenGLWidget::resizeGL(int w, int h){
    camera->setPerspective(45.0f, w / float(h), 0.0f, 1000.0f);
}

//**********************************************************************//

void OpenGLWidget::update()
{
  QOpenGLWidget::update();
}

//**********************************************************************//

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{   
    if(event->buttons() == Qt::RightButton){
        qDebug()<<"("<< event->x()<< ","<< event->y()<< ") ->"<<event->x()-mouseX<< ","<<event->y()-mouseY;

        float angleX,angleY;
        angleY=-(event->y()- mouseY);
        angleX=-(event->x()- mouseX);

        camera->rotate(angleY, angleX);

        mouseX=event->x();
        mouseY=event->y();
    }
}

//**********************************************************************//

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        qDebug()<<"(Despulsado)";
    }

}

//**********************************************************************//

void OpenGLWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        offsetX=event->x();
        offsetY=event->y();

        mouseX=event->x();
        mouseY=event->y();
        qDebug()<<"(Pulsado)";
    }
}
