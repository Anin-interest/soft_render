#pragma once
#include "polygon.h"
#include "maincamera.h"
#include "light.h"
#include <QString>

class BaseShader
{
public:
    BaseShader() = default;
    virtual ~BaseShader() = default;

	virtual void setCam(maincamera* camera) = 0;
    virtual V2F vertexShader(const Vertex& in) = 0;
    virtual Vector4 fragmentShader(const V2F& in) = 0;
	virtual int genTexture(QString& path) = 0;
	virtual Vector4 getTexture(int id, const V2F& in) = 0;
	virtual void setTextureID(int id) = 0;
	virtual void setMaterial(Material* m) = 0;
	virtual void setLight(Light* l) = 0;
};