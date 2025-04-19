#include "objmodel.h"
#include <fstream>

ObjModel::ObjModel(const QString& path)
{
    loadObjFile(path);
}

ObjModel::~ObjModel()
{
	vertices.clear();
	indices.clear();
}

void ObjModel::loadObjFile(const QString& path)
{
    static int cnt = 25;
    // obj loader.
    ifstream in;
    in.open(path.toStdString(), ifstream::in);
    if (in.fail()) return;
    string line;
    minPoint = Vector3(+10000000000, +10000000000, +10000000000);
    maxPoint = Vector3(-10000000000, -10000000000, -10000000000);
    vector<Vector3> t_vertices;
    vector<Vector3> t_normals;
    vector<Vector2> t_texcoords;
    while (!in.eof())
    {
        getline(in, line);
        istringstream iss(line.c_str());
        char trash;
        //vertex
        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vector3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            t_vertices.push_back(vertex);
            if (minPoint.x > vertex.x)minPoint.x = vertex.x;
            if (minPoint.y > vertex.y)minPoint.y = vertex.y;
            if (minPoint.z > vertex.z)minPoint.z = vertex.z;
            if (maxPoint.x < vertex.x)maxPoint.x = vertex.x;
            if (maxPoint.y < vertex.y)maxPoint.y = vertex.y;
            if (maxPoint.z < vertex.z)maxPoint.z = vertex.z;
        }
        // normal
        else if (!line.compare(0, 3, "vn "))
        {
            iss >> trash >> trash;
            Vector3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normal.normalize();
            t_normals.push_back(normal);
        }
        // texcoord
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            Vector2 texcoord;
            iss >> texcoord.x >> texcoord.y;
            t_texcoords.push_back(texcoord);
        }
        // face
        else if (!line.compare(0, 2, "f "))
        {
            iss >> trash;
            int index[3];
            while (iss >> index[0] >> trash >> index[1] >> trash >> index[2])
            {
                Vertex data;
                data.position = t_vertices[index[0] - 1];
                data.texcoord = t_texcoords[index[1] - 1];
                data.normal = t_normals[index[2] - 1];
                data.color = Vector4(0.2, 0.2, 0.2, 1.0);
                indices.push_back(vertices.size());
                vertices.push_back(data);
            }
        }
        else {
            if (!cnt)in.close();
            //cnt--;
        }
    }

    in.close();
}
