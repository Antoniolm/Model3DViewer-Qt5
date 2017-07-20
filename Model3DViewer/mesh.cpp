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
    vertex.push_back(QVector3D(-0.5f, -0.5f, +0.5f));
    vertex.push_back(QVector3D(-0.5f, +0.5f, +0.5f));
    vertex.push_back(QVector3D(+0.5f, +0.5f, +0.5f));
    vertex.push_back(QVector3D(+0.5f, -0.5f, +0.5f));

    vertex.push_back(QVector3D(-0.5f, -0.5f, -0.5f));
    vertex.push_back(QVector3D(-0.5f, +0.5f, -0.5f));
    vertex.push_back(QVector3D(+0.5f, +0.5f, -0.5f));
    vertex.push_back(QVector3D(+0.5f, -0.5f, -0.5f));

    index.push_back(0);index.push_back(2);index.push_back(1);
    index.push_back(0);index.push_back(3);index.push_back(2);

    index.push_back(7);index.push_back(5);index.push_back(6);
    index.push_back(7);index.push_back(4);index.push_back(5);

    index.push_back(4);index.push_back(1);index.push_back(5);
    index.push_back(4);index.push_back(0);index.push_back(1);

    index.push_back(3);index.push_back(6);index.push_back(2);
    index.push_back(3);index.push_back(7);index.push_back(6);

    index.push_back(1);index.push_back(6);index.push_back(5);
    index.push_back(1);index.push_back(2);index.push_back(6);

    index.push_back(4);index.push_back(3);index.push_back(0);
    index.push_back(4);index.push_back(7);index.push_back(3);
}

//**********************************************************************//

Mesh::Mesh(const string & aFile){
    FileObj * fileObj=FileObj::getInstance();
    fileObj->readEverything(aFile.c_str(),vertex,index,normals,textCoord,true,true);
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

void Mesh::setMesh(const string & aFile){
    FileObj * fileObj=FileObj::getInstance();
    fileObj->readEverything(aFile.c_str(),vertex,index,normals,textCoord,true,true);
}

//**********************************************************************//

void Mesh::initialize(QOpenGLShaderProgram *shader){
    // Create Vertex Array Object
    object.create();
    object.bind();

    //Create buffer
    buffer[POSITION_VB]= QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    buffer[POSITION_VB].create();
    buffer[POSITION_VB].bind();
    buffer[POSITION_VB].setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer[POSITION_VB].allocate(&vertex[0], vertex.size()*sizeof(QVector3D) );
    shader->enableAttributeArray(0);
    shader->setAttributeBuffer(0, GL_FLOAT, GL_FALSE, 3, 0);

    buffer[INDEX_VB]= QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    buffer[INDEX_VB].create();
    buffer[INDEX_VB].bind();
    buffer[INDEX_VB].setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer[INDEX_VB].allocate(&index[0], index.size() * sizeof(unsigned short));

    buffer[POSITION_VB].release();
    buffer[NORMAL_VB].release();
    buffer[TEXCOORD_VB].release();

    vertex.clear();
    //index.clear();
    normals.clear();
    textCoord.clear();

    object.release();

}

//**********************************************************************//

void Mesh::visualization(){
    object.bind();
    glDrawElements(GL_TRIANGLES,index.size(),GL_UNSIGNED_SHORT,0);
    object.release();
}

//**********************************************************************//

void Mesh::updateState(){

}

