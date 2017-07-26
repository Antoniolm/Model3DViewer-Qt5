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
    camera.setToIdentity();
    projection.setToIdentity();
}

//**********************************************************************//

Camera::Camera(QVector3D pos,QVector3D tgt, QVector3D orientation){
    position=pos;
    target=tgt;
    up=orientation;

    camera.lookAt(pos,tgt,orientation);
    projection.setToIdentity();
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

void Camera::setCamera(QVector3D pos,QVector3D tgt, QVector3D orientation){
    position=pos;
    target=tgt;
    up=orientation;

    camera.lookAt(pos,tgt,orientation);
}

//**********************************************************************//

QVector3D & Camera::getPosition(){
    return position;
}

//**********************************************************************//

QVector3D & Camera::getTarget(){
    return target;
}

//**********************************************************************//

QVector3D & Camera::getUp(){
    return up;
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

//**********************************************************************//

void Camera::rotate(float nAngleX,float nAngleY){
    QMatrix4x4 rotX;
    QMatrix4x4 rotY;
    rotX.rotate(nAngleX,1.0,0.0,0.0);
    rotY.rotate(nAngleY,0.0,1.0,0.0);

    QVector3D newPos=rotX*position;
    newPos=rotY*newPos;

    camera.lookAt(target,newPos,up);
}
