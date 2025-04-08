#include "basicshader.h"

V2F BasicShader::vertexShader(const Vertex& in) {
    V2F ret;
    ret.x = in.position.x;
    ret.y = in.position.y;
    ret.posM2W = in.position;
    ret.posV2P = in.position;
    ret.color = in.color;
    ret.normal = in.normal;
    ret.oneDivZ = 1.0;
    ret.texcoord = in.texcoord;
    return ret;
}

Vector4D BasicShader::fragmentShader(const V2F& in) {
    Vector4D retColor;
    retColor = in.color;
    return retColor;
}