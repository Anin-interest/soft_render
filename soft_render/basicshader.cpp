#include "basicshader.h"

BasicShader::BasicShader()
{
	textureID = -1;
    Mm2w.normalize();
    Mw2v.normalize();
    Mv2p.normalize();
}

BasicShader::~BasicShader()
{
	for (auto& texture : textures) {
		delete texture;
	}
	textures.clear();
}

void BasicShader::setCam(maincamera* cam)
{
    Mw2v.lookat(cam->pos, cam->goal, cam->up);
    Mv2p.perspective(cam->fov, cam->asp, cam->near, cam->far);
}

int BasicShader::genTexture(QString& path) {
	Textures* texture = new Textures();
	texture->loadImage(path);
	textures.push_back(texture);
	return textures.size() - 1;
}

Vector4 BasicShader::getTexture(int id, const V2F& in) {
	if (id < 0 || id >= textures.size()) {
        return in.color;
	}
	return textures[id]->sample(in.texcoord);
}

V2F BasicShader::vertexShader(const Vertex& in) {
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

Vector4 BasicShader::fragmentShader(const V2F& in) {
    Vector4 retColor = getTexture(in.textureID, in);
    return retColor;
}