#pragma once
#include "polygon.h"
#include <QString>

class BaseShader
{
public:
    BaseShader() = default;
    virtual ~BaseShader() = default;

	virtual void setCam(Vector3 pos, Vector3 goal, Vector3 up, float fov, float asp, float near, float far) = 0;
    virtual V2F vertexShader(const Vertex& in) = 0;
    virtual Vector4 fragmentShader(const V2F& in) = 0;
	virtual int genTexture(QString& path) = 0;
	virtual Vector4 getTexture(int id, const V2F& in) = 0;
};