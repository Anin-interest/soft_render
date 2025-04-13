#include "basicshader.h"

BasicShader::BasicShader()
{
	texcount = 0;
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

void BasicShader::setCam(Vector3 pos, Vector3 goal, Vector3 up, float fov, float asp, float near, float far)
{
    Mw2v.lookat(pos, goal, up);
    Mv2p.perspective(fov, asp, near, far);
}

int BasicShader::genTexture(QString& path) {
	Textures* texture = new Textures();
	texture->loadImage(path);
	textures.push_back(texture);
	return textures.size() - 1;
}

Vector4 BasicShader::getTexture(int id, const V2F& in) {
	if (id < 0 || id >= textures.size()) {
		//return Vector4(1.0, 1.0, 1.0, 0.0);
		return Vector4(0.0, 0.0, 0.0, 1.0);
	}
	return textures[id]->sample(in.texcoord);
}

V2F BasicShader::vertexShader(const Vertex& in) {
    V2F ret;
    ret.posM2W = Mm2w * in.position;
    ret.posV2P = Mv2p * Mw2v * ret.posM2W;
    ret.color = in.color;
    ret.normal = in.normal;
    ret.texcoord = in.texcoord;
    ret.oneDivZ = 1.0;
    ret.textureID = 0;
    return ret;
}

Vector4 BasicShader::fragmentShader(const V2F& in) {
    Vector4 retColor = getTexture(in.textureID, in);
    return retColor;
}