#pragma once
#include "vector4.h"
#include <QMainWindow>
#include <QString>
class Textures
{
 private:
     int width, height, channel;
     QImage* pixelBuffer;
public:
     Textures();
     ~Textures();
     void loadImage(const QString & path); 
     Vector4 sample(const Vector2 & texcoord);
 };
