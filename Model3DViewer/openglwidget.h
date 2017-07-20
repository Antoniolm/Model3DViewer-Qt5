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

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "camera.h"
#include "mesh.h"

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class QExposeEvent;
class QOpenGLShaderProgram;

class OpenGLWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
public:
    OpenGLWidget(QWidget *parent = 0);
    virtual ~OpenGLWidget();
protected:
    /**
     * @brief Initialize our OpenGL context
    */
    void initializeGL();

    /**
     * @brief It will resize the size of our OpenGL widget
     * @param w -> Weight of our OpenGL widget
     * @param h -> Height of our OpenGL widget
     * @return void
    */
    void resizeGL(int w, int h);

    /**
     * @brief Draw our scene
     * @return void
     */
    void paintGL();

    /**
     * @brief Update our scene
     * @return void
     */
    void update();

private:
  QOpenGLShaderProgram *program;
  Camera *camera;
  Mesh * mesh;

};

#endif // OPENGLWIDGET_H
