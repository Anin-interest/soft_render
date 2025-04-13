#pragma once
#include "vector4.h"

class Vertex
{
public:
    Vector4 position;
    Vector4 color;
    Vector2 texcoord;
    Vector3 normal;

    Vertex() {}
    ~Vertex() {}
    Vertex(Vector4 pos, Vector4 col, Vector2 tex, Vector3 nor) :
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
	int textureID;
	Vector4 posM2W; // Model to World
	Vector4 posV2P; // View to Projection
    Vector2 texcoord;
    Vector3 normal;
    Vector4 color;
    float oneDivZ;

    V2F() = default;
    V2F(Vector4 pMW, Vector4 pVP, Vector2 tex, Vector3 nor, Vector4 col, float oZ) :
        posM2W(pMW), posV2P(pVP), texcoord(tex), normal(nor), color(col), oneDivZ(oZ) {
		textureID = -1;
    }
    V2F(const V2F& ver) :
		textureID(ver.textureID),
        posM2W(ver.posM2W),
        posV2P(ver.posV2P),
        texcoord(ver.texcoord),
        normal(ver.normal),
        color(ver.color),
        oneDivZ(ver.oneDivZ) {
    }
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

	Mesh() = default;
    ~Mesh() = default;

    Mesh(const Mesh& msh) :vertices(msh.vertices), indices(msh.indices) {}
    Mesh& operator=(const Mesh& msh);
    void setVertices(Vertex* v, int count);
    void setIndices(int* i, int count);

    void triangle(Vector3& v1, Vector3& v2, Vector3& v3);
    void pyramid();
    void asBox(float width, float height, float depth);
    //void plane(float width, float height, int id, Vector4 pos);
};
