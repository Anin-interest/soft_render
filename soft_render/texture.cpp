#include "texture.h"

Textures::Textures()
{
    width = 0;
    height = 0;
    channel = 0;
    pixelBuffer = nullptr;
}
Textures::~Textures() {
	if (pixelBuffer != nullptr)
	{
		delete pixelBuffer;
		pixelBuffer = nullptr;
	}
	width = 0;
	height = 0;
	channel = 0;
}
void Textures::loadImage(const QString& path)
{
    pixelBuffer = new QImage();
    pixelBuffer->load(path);
    width = pixelBuffer->width();
    height = pixelBuffer->height();
	channel = pixelBuffer->format() == QImage::Format_RGBA8888 ? 4 : 3;
}
Vector4 Textures::sample(const Vector2& texcoord)
{
    Vector4 result(0.0, 0.0, 0.0, 1.0);
	if (pixelBuffer == nullptr)
	{
		return result;
	}
    unsigned int x = 0, y = 0;
    if (texcoord.x >= 0.0f && texcoord.x <= 1.0f && texcoord.y >= 0.0f && texcoord.y <= 1.0f)
    {
        float trueU = texcoord.x * (width - 1);
        float trueV = texcoord.y * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
    }
    else
    {
        float u = texcoord.x, v = texcoord.y;
        if (texcoord.x > 1.0f)
            u = texcoord.x - static_cast<int>(texcoord.x);
        else if (texcoord.x < 0.0f)
            u = 1.0f - (static_cast<int>(texcoord.x) - texcoord.x);
        if (texcoord.y > 1.0f)
            v = texcoord.y - static_cast<int>(texcoord.y);
        else if (texcoord.y < 0.0f)
            v = 1.0f - (static_cast<int>(texcoord.y) - texcoord.y);
        float trueU = u * (width - 1);
        float trueV = v * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
    }

    result.x = static_cast<float>(pixelBuffer->pixelColor(x, y).red()) * 1.0f / 255;
    result.y = static_cast<float>(pixelBuffer->pixelColor(x, y).green()) * 1.0f / 255;
    result.z = static_cast<float>(pixelBuffer->pixelColor(x, y).blue()) * 1.0f / 255;
	result.w = static_cast<float>(pixelBuffer->pixelColor(x, y).alpha()) * 1.0f / 255;

    return result;
}