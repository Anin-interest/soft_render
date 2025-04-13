#pragma once
#include "baseshader.h"
#include "matrix.h"
#include "texture.h"

class BasicShader : public BaseShader
{
private:
    Matrix Mm2w;
    Matrix Mw2v;
    Matrix Mv2p;
	std::vector<Textures*> textures;
    int texcount;
    
public:
    BasicShader();
    ~BasicShader();
    void setCam(Vector3 pos, Vector3 goal, Vector3 up, float fov, float asp, float near, float far);
    V2F vertexShader(const Vertex& in);
    Vector4 fragmentShader(const V2F& in);
    int genTexture(QString& path);
    Vector4 getTexture(int id, const V2F& in);
};