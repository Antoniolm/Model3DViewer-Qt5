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

Mesh::Mesh(){
    // Create a colored cube
    sg_vertexes.push_back(QVector3D(-0.5f, -0.5f, +0.5f));
    sg_vertexes.push_back(QVector3D(-0.5f, +0.5f, +0.5f));
    sg_vertexes.push_back(QVector3D(+0.5f, +0.5f, +0.5f));
    sg_vertexes.push_back(QVector3D(+0.5f, -0.5f, +0.5f));

    sg_vertexes.push_back(QVector3D(-0.5f, -0.5f, -0.5f));
    sg_vertexes.push_back(QVector3D(-0.5f, +0.5f, -0.5f));
    sg_vertexes.push_back(QVector3D(+0.5f, +0.5f, -0.5f));
    sg_vertexes.push_back(QVector3D(+0.5f, -0.5f, -0.5f));
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
    unsigned short cubeIndices[] ={
            // front plane
            0, 2, 1,
            0, 3, 2,
            // back plane
            7, 5, 6,
            7, 4, 5,
            // left plane
            4, 1, 5,
            4, 0, 1,
            // right plane
            3, 6, 2,
            3, 7, 6,
            // top plane
            1, 6, 5,
            1, 2, 6,
            // bottom plane
            4, 3, 0,
            4, 7, 3
        };

    // Create Vertex Array Object
    object.create();
    object.bind();

    //Create buffer
    buffer[POSITION_VB]= QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    buffer[POSITION_VB].create();
    buffer[POSITION_VB].bind();
    buffer[POSITION_VB].setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer[POSITION_VB].allocate(&sg_vertexes[0], sg_vertexes.size()*sizeof(QVector3D) );
    shader->enableAttributeArray(0);
    shader->setAttributeBuffer(0, GL_FLOAT, GL_FALSE, 3, 0);

    buffer[INDEX_VB]= QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    buffer[INDEX_VB].create();
    buffer[INDEX_VB].bind();
    buffer[INDEX_VB].setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer[INDEX_VB].allocate(cubeIndices, 36 * sizeof(unsigned short));

    buffer[POSITION_VB].release();
    buffer[NORMAL_VB].release();
    buffer[TEXCOORD_VB].release();
    object.release();

}

//**********************************************************************//

void Mesh::visualization(){
    object.bind();
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,0);
    object.release();
}

//**********************************************************************//

void Mesh::updateState(){

}

