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

#include "fileobj.h"
#include "QFile"
#include "QTextStream"

FileObj* FileObj::instance = NULL;

FileObj::FileObj()
{

}

void FileObj::readEverything(const char * fileName,std::vector<QVector3D> & vertex,std::vector<unsigned short> & triangles,
                    std::vector<QVector3D> & normals,std::vector<QVector2D> & textureCord,bool flagNormal,bool flagOrigin){
    int value;
    char charValue;
    float x,y,z;
    istringstream * readerStr;
    std::vector<QVector3D> vertexAux;
    std::vector<QVector3D> normalsVertex;
    std::vector<QVector2D> textureVertex;
    std::vector<unsigned short> trianglesIndex;
    std::vector<int> normalFaces;
    std::vector<int> textureFaces;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    /*if (file.open(QIODevice::ReadOnly)) {
        cout<< "Exploto"<< fileName<< endl;

        stream << "something" << endl;
    }*/

    /*ifstream in(fileName, ios::in);
    if (!in)
    {
        cout<< "Cannot open " << fileName << endl;
    }
    else{
        cout<< "Geometry ->"<< fileName<< endl;
    }*/

    string line;
    while (!stream.atEnd())
    {
        line=stream.readLine().toStdString();
        if (line.substr(0,2) == "v "){ //Extract vertex
            readerStr=new istringstream(line.substr(2));
            (*readerStr) >> x;
            (*readerStr) >> y;
            (*readerStr) >> z;
            vertexAux.push_back(QVector3D(x,y,z));
        }
        else if (line.substr(0,3) == "vn "){ //Extract normal face
            readerStr=new istringstream(line.substr(3));
            (*readerStr) >> x;
            (*readerStr) >> y;
            (*readerStr) >> z;
            normalsVertex.push_back(QVector3D(x,y,z));

        }
        else if (line.substr(0,3) == "vt "){ //Extract texture Coord
            readerStr=new istringstream(line.substr(3));
            (*readerStr) >> x;
            (*readerStr) >> y;
            textureVertex.push_back(QVector2D(x,y));

        }
        else if (line.substr(0,2) == "f "){
            readerStr=new istringstream(line.substr(2));
            for(int i=0;i<3;i++){
                //Extract the triangle face
                (*readerStr) >> value;
                trianglesIndex.push_back(--value);

                //Extract the texture face
                (*readerStr) >> charValue; //Extract the char between element
                (*readerStr) >> value;
                textureFaces.push_back(--value);

                //Extract the normals face
                (*readerStr) >> charValue; //Extract the char between element
                (*readerStr) >> value;
                normalFaces.push_back(--value);
            }
        }

    }
    if(flagOrigin){
        QVector3D origin=calculate_origin(vertexAux);
        for(unsigned i=0;i< vertexAux.size();i++){
            vertexAux[i]=vertexAux[i]-origin;

        }

    }
    std::vector<QVector3D> normalAux;
    if(flagNormal)
        calculate_normals(vertexAux,trianglesIndex,normalAux);

    for(unsigned i=0;i<trianglesIndex.size();i++){
        vertex.push_back(vertexAux[trianglesIndex[i]]);

        if(flagNormal)
            normals.push_back(normalAux[trianglesIndex[i]]);
        else
            normals.push_back(normalsVertex[normalFaces[i]]);

        textureCord.push_back(textureVertex[textureFaces[i]]);
        triangles.push_back(i);
    }
}

void FileObj::calculate_normals(std::vector<QVector3D> & vertex,std::vector<unsigned short> & triangles,std::vector<QVector3D> & normals){
    //Calculate face normals
    QVector3D v1,v2,normalFace;

    for(unsigned i=0;i<vertex.size();i++){
        normals.push_back(QVector3D(0.0,0.0,0.0));
    }

    for(unsigned i=0;i<triangles.size();i=i+3){
        int i0 = triangles[i];
        int i1 = triangles[i + 1];
        int i2 = triangles[i + 2];

        v1=vertex[i1]-vertex[i0];
        v2=vertex[i2]-vertex[i0];

        normalFace=QVector3D::crossProduct(v1,v2);
        normalFace.normalize();

        normals[i0]=normals[i0] + normalFace;
        normals[i1]=normals[i1] + normalFace;
        normals[i2]=normals[i2] + normalFace;
    }

    for(unsigned k=0;k<vertex.size();k++){
        normals[k].normalize();
    }

}

QVector3D FileObj::calculate_origin(std::vector<QVector3D> & vertex){
    float maxX,maxY,maxZ,minX,minY,minZ;
    maxX=vertex[0].x();  maxY=vertex[0].y();  maxZ=vertex[0].z();
    minX=vertex[0].x();  minY=vertex[0].y();  minZ=vertex[0].z();

    for(unsigned i=1;i<vertex.size();i++){
        if(vertex[i].x() >maxX) maxX=vertex[i].x();
        if(vertex[i].y() >maxY) maxY=vertex[i].y();
        if(vertex[i].z() >maxZ) maxZ=vertex[i].z();

        if(vertex[i].x() < minX) minX=vertex[i].x();
        if(vertex[i].y() < minY) minY=vertex[i].y();
        if(vertex[i].z() < minZ) minZ=vertex[i].z();
    }

    QVector3D result(minX+((maxX-minX)/2.0),minY+((maxY-minY)/2.0),minZ+((maxZ-minZ)/2.0));

    return result;
}

