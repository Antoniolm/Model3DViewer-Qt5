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

Mesh::Mesh()
{

}

//**********************************************************************//

Mesh::Mesh(const string & aFile){

}

//**********************************************************************//

Mesh::~Mesh(){

}

//**********************************************************************//

void Mesh::setMesh(const string & aFile){

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

