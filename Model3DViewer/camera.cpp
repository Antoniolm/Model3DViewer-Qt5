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

#include "camera.h"
#include "QRect"

Camera::Camera(){
}

//**********************************************************************//

Camera::Camera(QVector3D position,QVector3D target, QVector3D up){
    camera.lookAt(position,target,up);
}

//**********************************************************************//

Camera::~Camera(){
}

//**********************************************************************//

void Camera::setPerspective(float verticalAngle,float aspectRatio,float nearPlan,float farPlan){
    projection.perspective(verticalAngle,aspectRatio,nearPlan,farPlan);
}

//**********************************************************************//

void Camera::setOrthographic(float left,float right,float bottom,float top){
    projection.ortho(QRect(right,top,left,bottom));
}

//**********************************************************************//

void Camera::setCamera(QVector3D position,QVector3D target, QVector3D up){
    camera.lookAt(position,target,up);
}

//**********************************************************************//

QMatrix4x4 & Camera::getCamera(){
    return camera;
}

//**********************************************************************//

QMatrix4x4 & Camera::getProjection(){
    return projection;
}

//**********************************************************************//

void Camera::activate(QOpenGLShaderProgram *shader){
    shader->setUniformValue(shader->uniformLocation("projection"), projection);
    shader->setUniformValue(shader->uniformLocation("view"), camera);
}
