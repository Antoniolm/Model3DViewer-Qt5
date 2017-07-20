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

#include "mesh.h"

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

Mesh::Mesh()
{

}

//**********************************************************************//

Mesh::Mesh(const QString & aFile){

}

//**********************************************************************//

Mesh::~Mesh(){
 object.destroy();
 buffer[POSITION_VB].destroy();
 buffer[NORMAL_VB].destroy();
 buffer[TEXCOORD_VB].destroy();
 buffer[INDEX_VB].destroy();
}

//**********************************************************************//

void Mesh::setMesh(const QString & aFile){

}

//**********************************************************************//

void Mesh::initialize(QOpenGLShaderProgram *shader){
    // Create Vertex Array Object
    object.create();
    object.bind();

    //Create buffer
    buffer[POSITION_VB].create();
    buffer[POSITION_VB].bind();
    buffer[POSITION_VB].setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer[POSITION_VB].allocate(sg_vertexes, sizeof(sg_vertexes));
    shader->enableAttributeArray(0);
    shader->setAttributeBuffer(0, GL_FLOAT, GL_FALSE, 3, sizeof(QVector3D));

    buffer[POSITION_VB].release();
    buffer[NORMAL_VB].release();
    buffer[TEXCOORD_VB].release();
    buffer[INDEX_VB].release();
    object.release();

}

//**********************************************************************//

void Mesh::visualization(){
    object.bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    object.release();
}

//**********************************************************************//

void Mesh::updateState(){

}

