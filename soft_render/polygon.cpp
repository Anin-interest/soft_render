#include "polygon.h"

V2F V2F::lerp(const V2F& v1, const V2F& v2, double weight)
{
	return V2F(
		posM2W.lerp(v1.posM2W, v2.posM2W, weight),
		posV2P.lerp(v1.posV2P, v2.posV2P, weight),
		texcoord.lerp(v1.texcoord, v2.texcoord, weight),
		normal.lerp(v1.normal, v2.normal, weight),
		color.lerp(v1.color, v2.color, weight),
		oneDivZ * (1.0 - weight) + v2.oneDivZ * weight
	);
}

Mesh& Mesh::operator=(const Mesh& msh)
{
    vertices = msh.vertices;
    index = msh.index;
    return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
    vertices.resize(static_cast<unsigned long>(count));
    new(&vertices[0])std::vector<Vertex>(v, v + count);
}

void Mesh::setIndex(int* i, int count)
{
    index.resize(static_cast<unsigned long>(count));
    new(&index)std::vector<unsigned int>(i, i + count);
}

void Mesh::triangle(Vector3D& v1, Vector3D& v2, Vector3D& v3)
{
    vertices.resize(3);
    index.resize(3);
    vertices[0].position = v1;
    vertices[0].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[0].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vector2D(0.f, 0.f);
    vertices[1].position = v2;
    vertices[1].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[1].color = Vector4D(0.f, 1.f, 0.f, 1.f);
    vertices[1].texcoord = Vector2D(1.f, 0.f);
    vertices[2].position = v3;
    vertices[2].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[2].color = Vector4D(0.f, 0.f, 1.f, 1.f);
    vertices[2].texcoord = Vector2D(0.5f, 1.f);
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
}