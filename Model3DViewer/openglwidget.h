#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

class QExposeEvent;
class QOpenGLShaderProgram;

class OpenGLWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
public:
    OpenGLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // OPENGLWIDGET_H
