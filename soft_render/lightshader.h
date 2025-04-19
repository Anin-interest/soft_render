#pragma once
#include "baseshader.h"
#include "light.h"
#include "matrix.h"
#include "texture.h"

class LightShader : public BaseShader
{
private:
	Light* light;
	Material* material;

	Matrix Mm2w;
	Matrix Mw2v;
	Matrix Mv2p;
	Matrix inv_Mm2w;
	Vector3 eye;
	std::vector<Textures*> textures;
	int textureID;

public:
	LightShader();
	~LightShader();

	virtual void setCam(maincamera* camera);
	virtual V2F vertexShader(const Vertex& in);
	virtual Vector4 fragmentShader(const V2F& in);
	virtual int genTexture(QString& path);
	virtual Vector4 getTexture(int id, const V2F& in);
	virtual void setTextureID(int id) { textureID = id; }
	virtual void setMaterial(Material* m) { material = m; }
	virtual void setLight(Light* l) { light = l; }

};

