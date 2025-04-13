#include "polygon.h"

Mesh& Mesh::operator=(const Mesh& msh)
{
	if (this == &msh) return *this;
    vertices = msh.vertices;
    indices = msh.indices;
    return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
    vertices.resize(static_cast<unsigned long>(count));
    new(&vertices[0])std::vector<Vertex>(v, v + count);
}

void Mesh::setIndices(int* i, int count)
{
    indices.resize(static_cast<unsigned long>(count));
    new(&indices)std::vector<unsigned int>(i, i + count);
}

void Mesh::triangle(Vector3& v1, Vector3& v2, Vector3& v3)
{
    vertices.resize(3);
    indices.resize(3);
    vertices[0].position = v1;
    vertices[0].normal = Vector3(0.f, 0.f, 1.f);
    vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vector2(0.f, 0.f);
    vertices[1].position = v2;
    vertices[1].normal = Vector3(0.f, 0.f, 1.f);
    vertices[1].color = Vector4(0.f, 1.f, 0.f, 1.f);
    vertices[1].texcoord = Vector2(1.f, 0.f);
    vertices[2].position = v3;
    vertices[2].normal = Vector3(0.f, 0.f, 1.f);
    vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
    vertices[2].texcoord = Vector2(0.5f, 1.f);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
}

void Mesh::pyramid()
{
	// ÈýÀâ×¶
	vertices.resize(5);
	indices.resize(18);
	float a = 2;
	vertices[0].position = Vector4(a * 0.f,a * 1.f,a * 0.f, 1.0f);
	vertices[1].position = Vector4(a * -1.f,a * 0.f,a * -1.f, 1.0f);
	vertices[2].position = Vector4(a * 1.f,a * 0.f,a * -1.f, 1.0f);
	vertices[3].position = Vector4(a * 1.f,a * 0.f,a * 1.f, 1.0f);
	vertices[4].position = Vector4(a * -1.f,a * 0.f,a * 1.f, 1.0f);
	for (int i = 0; i < 5; i++)
		vertices[i].normal = Vector3(0.f, 0.f, 1.f);
	for (int i = 0; i < 5; i++)
		//vertices[i].color = Vector4(0.2f, 0.2f, 0.2f, 1.f);
		vertices[i].color = Vector4((i) & 1, (i >> 1) & 1, (i >> 2) & 1, 1.0f);
	vertices[0].texcoord = Vector2(0.5f, 1.f);
	vertices[1].texcoord = Vector2(0.f, 0.f);
	vertices[2].texcoord = Vector2(1.f, 0.f);
	vertices[3].texcoord = Vector2(1.f, 1.f);
	vertices[4].texcoord = Vector2(0.f, 1.f);
	// ²àÃæ
	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;
	indices[6] = 0;
	indices[7] = 4;
	indices[8] = 3;
	indices[9] = 0;
	indices[10] = 1;
	indices[11] = 4;
	// µ×Ãæ
	indices[12] = 1;
	indices[13] = 2;
	indices[14] = 3;
	indices[15] = 1;
	indices[16] = 3;
	indices[17] = 4;
}

void Mesh::asBox(float width, float height, float depth)
{
    vertices.resize(24);
    indices.resize(36);

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;
    float halfD = depth * 0.5f;
    //front
    vertices[0].position = Vector3(halfW, halfH, halfD);
    vertices[0].normal = Vector3(0.f, 0.f, 1.f);
    vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vector2(1.f, 1.f);
    vertices[1].position = Vector3(-halfW, halfH, halfD);
    vertices[1].normal = Vector3(0.f, 0.f, 1.f);
    vertices[1].color = Vector4(0.f, 1.f, 0.f, 1.f);
    vertices[1].texcoord = Vector2(0.f, 1.f);
    vertices[2].position = Vector3(-halfW, -halfH, halfD);
    vertices[2].normal = Vector3(0.f, 0.f, 1.f);
    vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
    vertices[2].texcoord = Vector2(0.f, 0.f);
    vertices[3].position = Vector3(halfW, -halfH, halfD);
    vertices[3].normal = Vector3(0.f, 0.f, 1.f);
    vertices[3].color = Vector4(0.f, 1.f, 1.f, 1.f);
    vertices[3].texcoord = Vector2(1.f, 0.f);
    //left
    vertices[4].position = Vector3(-halfW, +halfH, halfD);
    vertices[4].normal = Vector3(-1.f, 0.f, 0.f);
    vertices[4].color = Vector4(0.f, 0.f, 1.f, 1.f);
    vertices[4].texcoord = Vector2(1.f, 1.f);
    vertices[5].position = Vector3(-halfW, +halfH, -halfD);
    vertices[5].normal = Vector3(-1.f, 0.f, 0.f);
    vertices[5].color = Vector4(1.f, 1.f, 0.f, 1.f);
    vertices[5].texcoord = Vector2(0.f, 1.f);
    vertices[6].position = Vector3(-halfW, -halfH, -halfD);
    vertices[6].normal = Vector3(-1.f, 0.f, 0.f);
    vertices[6].color = Vector4(0.f, 1.f, 0.f, 1.f);
    vertices[6].texcoord = Vector2(0.f, 0.f);
    vertices[7].position = Vector3(-halfW, -halfH, halfD);
    vertices[7].normal = Vector3(-1.f, 0.f, 0.f);
    vertices[7].color = Vector4(1.f, 1.f, 1.f, 1.f);
    vertices[7].texcoord = Vector2(1.f, 0.f);
    //back
    vertices[8].position = Vector3(-halfW, +halfH, -halfD);
    vertices[8].normal = Vector3(0.f, 0.f, -1.f);
    vertices[8].color = Vector4(1.f, 0.f, 1.f, 1.f);
    vertices[8].texcoord = Vector2(0.f, 0.f);
    vertices[9].position = Vector3(+halfW, +halfH, -halfD);
    vertices[9].normal = Vector3(0.f, 0.f, -1.f);
    vertices[9].color = Vector4(0.f, 1.f, 1.f, 1.f);
    vertices[9].texcoord = Vector2(1.f, 0.f);
    vertices[10].position = Vector3(+halfW, -halfH, -halfD);
    vertices[10].normal = Vector3(0.f, 0.f, -1.f);
    vertices[10].color = Vector4(1.f, 1.f, 0.f, 1.f);
    vertices[10].texcoord = Vector2(1.f, 1.f);
    vertices[11].position = Vector3(-halfW, -halfH, -halfD);
    vertices[11].normal = Vector3(0.f, 0.f, -1.f);
    vertices[11].color = Vector4(0.f, 0.f, 1.f, 1.f);
    vertices[11].texcoord = Vector2(0.f, 1.f);
    //right
    vertices[12].position = Vector3(halfW, +halfH, -halfD);
    vertices[12].normal = Vector3(1.f, 0.f, 0.f);
    vertices[12].color = Vector4(0.f, 1.f, 0.f, 1.f);
    vertices[12].texcoord = Vector2(0.f, 0.f);
    vertices[13].position = Vector3(halfW, +halfH, +halfD);
    vertices[13].normal = Vector3(1.f, 0.f, 0.f);
    vertices[13].color = Vector4(1.f, 0.f, 0.f, 1.f);
    vertices[13].texcoord = Vector2(1.f, 0.f);
    vertices[14].position = Vector3(halfW, -halfH, +halfD);
    vertices[14].normal = Vector3(1.f, 0.f, 0.f);
    vertices[14].color = Vector4(0.f, 1.f, 1.f, 1.f);
    vertices[14].texcoord = Vector2(1.f, 1.f);
    vertices[15].position = Vector3(halfW, -halfH, -halfD);
    vertices[15].normal = Vector3(1.f, 0.f, 0.f);
    vertices[15].color = Vector4(1.f, 0.f, 1.f, 1.f);
    vertices[15].texcoord = Vector2(0.f, 1.f);
    //top
    vertices[16].position = Vector3(+halfW, halfH, -halfD);
    vertices[16].normal = Vector3(0.f, 1.f, 0.f);
    vertices[16].color = Vector4(0.f, 0.f, 0.f, 1.f);
    vertices[16].texcoord = Vector2(0.f, 0.f);
    vertices[17].position = Vector3(-halfW, halfH, -halfD);
    vertices[17].normal = Vector3(0.f, 1.f, 0.f);
    vertices[17].color = Vector4(1.f, 1.f, 0.f, 1.f);
    vertices[17].texcoord = Vector2(1.f, 0.f);
    vertices[18].position = Vector3(-halfW, halfH, halfD);
    vertices[18].normal = Vector3(0.f, 1.f, 0.f);
    vertices[18].color = Vector4(0.f, 1.f, 1.f, 1.f);
    vertices[18].texcoord = Vector2(1.f, 1.f);
    vertices[19].position = Vector3(+halfW, halfH, halfD);
    vertices[19].normal = Vector3(0.f, 1.f, 0.f);
    vertices[19].color = Vector4(1.f, 0.f, 0.f, 1.f);
    vertices[19].texcoord = Vector2(0.f, 1.f);
    //down
    vertices[20].position = Vector3(+halfW, -halfH, -halfD);
    vertices[20].normal = Vector3(0.f, -1.f, 0.f);
    vertices[20].color = Vector4(0.f, 0.f, 1.f, 1.f);
    vertices[20].texcoord = Vector2(0.f, 0.f);
    vertices[21].position = Vector3(+halfW, -halfH, +halfD);
    vertices[21].normal = Vector3(0.f, -1.f, 0.f);
    vertices[21].color = Vector4(1.f, 1.f, 1.f, 1.f);
    vertices[21].texcoord = Vector2(1.f, 0.f);
    vertices[22].position = Vector3(-halfW, -halfH, +halfD);
    vertices[22].normal = Vector3(0.f, -1.f, 0.f);
    vertices[22].color = Vector4(0.f, 1.f, 0.f, 1.f);
    vertices[22].texcoord = Vector2(1.f, 1.f);
    vertices[23].position = Vector3(-halfW, -halfH, -halfD);
    vertices[23].normal = Vector3(0.f, -1.f, 0.f);
    vertices[23].color = Vector4(1.f, 0.f, 1.f, 1.f);
    vertices[23].texcoord = Vector2(0.f, 1.f);

    //front
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    //left
    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;
    indices[9] = 4;
    indices[10] = 6;
    indices[11] = 7;
    //back
    indices[12] = 8;
    indices[13] = 9;
    indices[14] = 10;
    indices[15] = 8;
    indices[16] = 10;
    indices[17] = 11;
    //right
    indices[18] = 12;
    indices[19] = 13;
    indices[20] = 14;
    indices[21] = 12;
    indices[22] = 14;
    indices[23] = 15;
    //top
    indices[24] = 16;
    indices[25] = 17;
    indices[26] = 18;
    indices[27] = 16;
    indices[28] = 18;
    indices[29] = 19;
    //down
    indices[30] = 20;
    indices[31] = 21;
    indices[32] = 22;
    indices[33] = 20;
    indices[34] = 22;
    indices[35] = 23;
}