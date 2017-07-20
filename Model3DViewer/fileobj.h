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


#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include <vector>
#include <QVector3D>
#include <QVector2D>

using namespace std;

class FileObj
{
public:

    /**
    *    @brief The method will read a obj file and obtain all the vertex,triangles
    *    normals,textureCoord of them
    *    \return void
    */
    void readEverything(const char * fileName,std::vector<QVector3D> & vertex,std::vector<unsigned short> & triangles,
                        std::vector<QVector3D> & normals,std::vector<QVector2D> & textureCord, bool flagNormal,bool flagOrigin);

    /**
    *    @brief The method will calculate the normals of an object
    *    \return void
    */
    void calculate_normals(std::vector<QVector3D> & vertex,std::vector<unsigned short> & triangles,std::vector<QVector3D> & normals);

    /**
    *    @brief The method will calculate the origin of an object
    *    \return vec3f
    */
    QVector3D calculate_origin(std::vector<QVector3D> & vertex);

    /**
     * @brief It will return the unique instance of the class
     * @return
     */
    static FileObj * getInstance(){
        if(instance == NULL)
            instance = new FileObj();

        return instance;
    }
private:
    FileObj();

    static FileObj *instance;   //Instance of the fileObj

};

#endif // FILEOBJ_H
