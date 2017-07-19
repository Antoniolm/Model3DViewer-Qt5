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
    /**
     * @brief Constructor
     */
    Camera();

    /**
     * @brief Constructor
     * @param position -> Position of the camera
     * @param target -> target of the camera
     * @param up     -> Orientation of the camera
     */
    Camera(QVector3D position,QVector3D target, QVector3D up);

    /**
     * @brief Destructor
     */
    virtual ~Camera();

    /**
     * @brief It will set a perspective projection
     * @param verticalAngle
     * @param aspectRatio
     * @param nearPlan
     * @param farPlan
     */
    void setPerspective(float verticalAngle,float aspectRatio,float nearPlan,float farPlan);

    /**
     * @brief It will set an Orthographic projection
     * @param left
     * @param right
     * @param bottom
     * @param top
     */
    void setOrthographic(float left,float right,float bottom,float top);

    /**
     * @brief It will set the camera
     * @param position
     * @param target
     * @param up
     */
    void setCamera(QVector3D position,QVector3D target, QVector3D up);

    /**
     * @brief It will return the camera
     * @return
     */
    QMatrix4x4 & getCamera();

    /**
     * @brief It will return the projection
     * @return
     */
    QMatrix4x4 & getProjection();

    /**
     * @brief Activate the camera in the shader
     * @param shader -> Shader program where the camera will be activated
     */
    void activate(QOpenGLShaderProgram *shader);

private:
    QMatrix4x4 camera;
    QMatrix4x4 projection;
};

#endif // CAMERA_H
