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

#ifndef CAMERA_H
#define CAMERA_H

#include "QVector3D"
#include "QMatrix4x4"
#include <QOpenGLShaderProgram>

class Camera
{
public:
    Camera();
    Camera(QVector3D position,QVector3D target, QVector3D up);
    virtual ~Camera();

    void setPerspective(float verticalAngle,float aspectRatio,float nearPlan,float farPlan);
    void setOrthographic(float left,float right,float bottom,float top);
    void setCamera(QVector3D position,QVector3D target, QVector3D up);

    QMatrix4x4 & getCamera();
    QMatrix4x4 & getProjection();

    void activate(QOpenGLShaderProgram *shader);

private:
    QMatrix4x4 camera;
    QMatrix4x4 projection;
};

#endif // CAMERA_H
