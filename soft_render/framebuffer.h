#pragma once
#include "vector4.h"

class FrameBuffer
{
private:
    int width, height;
    unsigned char mp[8294405];
public:
    FrameBuffer(int w, int h) :width(w), height(h) {}
    ~FrameBuffer() {}
    void Fill(Vector4D vec);
    void Cover(int x, int y, Vector4D vec);
    unsigned char* getColorBuffer();
};
