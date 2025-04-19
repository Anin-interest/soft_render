#include "lightshader.h"

LightShader::LightShader()
{
    light = nullptr;
    material = nullptr;
    textureID = -1;
    Mm2w.normalize();
    Mw2v.normalize();
    Mv2p.normalize();
}

LightShader::~LightShader()
{
    for (auto& texture : textures) {
        delete texture;
    }
    textures.clear();
    delete light;
    delete material;
}

void LightShader::setCam(maincamera* cam)
{
    eye = cam->pos;
    Mw2v.lookat(cam->pos, cam->goal, cam->up);
    Mv2p.perspective(cam->fov, cam->asp, cam->near, cam->far);
}

int LightShader::genTexture(QString& path) {
    Textures* texture = new Textures();
    texture->loadImage(path);
    textures.push_back(texture);
    return textures.size() - 1;
}

Vector4 LightShader::getTexture(int id, const V2F& in) {
    if (id < 0 || id >= textures.size()) {
        return in.color;
    }
    return textures[id]->sample(in.texcoord);
}

V2F LightShader::vertexShader(const Vertex& in) {
    V2F ret;
    ret.posM2W = Mm2w * in.position;
    ret.posV2P = Mv2p * Mw2v * ret.posM2W;
    ret.color = in.color;
    ret.texcoord = in.texcoord;

    ret.oneDivZ = 1.f / ret.posV2P.w;
    ret.texcoord = ret.texcoord * ret.oneDivZ;
    ret.textureID = textureID;
    return ret;
}

Vector4 LightShader::fragmentShader(const V2F& in) {
    Vector4 retColor = getTexture(in.textureID, in);

    // Gouraud shading.
    Vector3 amb, diff, spec;
    if (light)
    {
        Vector3 eyeDir = eye - in.posM2W;
        eyeDir.normalize();
        light->lighting(*material, in.posM2W, in.normal, eyeDir, amb, diff, spec);

        retColor.x *= (amb.x + diff.x + spec.x);
        retColor.y *= (amb.y + diff.y + spec.y);
        retColor.z *= (amb.z + diff.z + spec.z);
        retColor.w = 1.0f;
    }

    return retColor;
}