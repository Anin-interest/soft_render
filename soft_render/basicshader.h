#pragma once
#include "shader.h"
class BasicShader :public Shader
{
public:
    BasicShader() {};
    ~BasicShader() {};

private:
    V2F vertexShader(const Vertex& in);
    Vector4D fragmentShader(const V2F& in);

};