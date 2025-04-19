#pragma once
#include <vector>
#include "vector4.h"

class FrameBuffer
{
private:
    int width, height, channel;
    std::vector<unsigned char> col;
    std::vector<float> depth;
public:
    FrameBuffer(int w, int h) :width(w), height(h), channel(4) {
        col.resize(w * h * channel, 255);
        depth.resize(w * h, 1.f);
    }
    ~FrameBuffer() {}
    void Fill(Vector4 vec, float dep);
    void Cover(int x, int y, Vector4 vec);
    unsigned char* getColorBuffer() {
		return col.data();
    }
	void  setDepthBuffer(int x, int y, float val) {
		if (x < 0 || x >= width || y < 0 || y >= height) return;
		depth[y * width + x] = val;
	}
    float getDepthBuffer(int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) return 0;
		return depth[y * width + x];
    }
};
