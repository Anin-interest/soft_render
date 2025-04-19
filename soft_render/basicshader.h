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
    int textureID;
    
public:
    BasicShader();
    ~BasicShader();
    virtual void setCam(maincamera* camera) ;
    virtual V2F vertexShader(const Vertex& in) ;
    virtual Vector4 fragmentShader(const V2F& in) ;
    virtual int genTexture(QString& path) ;
    virtual Vector4 getTexture(int id, const V2F& in) ;
    virtual void setTextureID(int id)  { textureID = id; }
    virtual void setMaterial(Material* m){}
    virtual void setLight(Light* l){}
};