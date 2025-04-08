#pragma once
#include "polygon.h"

class Shader
{
public:
    Shader() {}
    virtual ~Shader() {}
    virtual V2F vertexShader(const Vertex& in) = 0;
    virtual Vector4D fragmentShader(const V2F& in) = 0;
};
