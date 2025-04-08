#pragma once
#include <vector>
#include "vector2.h"
#include "vector4.h"

class Vertex
{
public:
    Vector4D position;
    Vector4D color;
    Vector2D texcoord;
    Vector3D normal;

    Vertex() {}
    ~Vertex() {}
    Vertex(Vector4D pos, Vector4D col, Vector2D tex, Vector3D nor) :
        position(pos), color(col), texcoord(tex), normal(nor) {
    }
    Vertex(const Vertex& ver) :
        position(ver.position),
        color(ver.color),
        texcoord(ver.texcoord),
        normal(ver.normal) {
    }
};
class V2F
{
public:
	int x, y;
	//int textureID;
    Vector4D posM2W;
    Vector4D posV2P;
    Vector2D texcoord;
    Vector3D normal;
    Vector4D color;
    double oneDivZ;

    V2F() {}
    V2F(Vector4D pMW, Vector4D pVP, Vector2D tex, Vector3D nor, Vector4D col, double oZ) :
        posM2W(pMW), posV2P(pVP), texcoord(tex), normal(nor), color(col), oneDivZ(oZ) {
    }
    V2F(const V2F& ver) :
		x(ver.x),
		y(ver.y),
		//textureID(ver.textureID),
        posM2W(ver.posM2W),
        posV2P(ver.posV2P),
        texcoord(ver.texcoord),
        normal(ver.normal),
        color(ver.color),
        oneDivZ(ver.oneDivZ) {
    }

    V2F lerp(const V2F& v1, const V2F& v2, double weight);
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> index;

    Mesh() {}
    ~Mesh() {}

    Mesh(const Mesh& msh) :vertices(msh.vertices), index(msh.index) {}
    Mesh& operator=(const Mesh& msh);
    void setVertices(Vertex* v, int count);
    void setIndex(int* i, int count);

    void triangle(Vector3D& v1, Vector3D& v2, Vector3D& v3);
    //void pyramid();
    //void cube(double width, double height, double depth, int id, Vector4D pos);
    //void plane(double width, double height, int id, Vector4D pos);
};
