#include "framebuffer.h"

void FrameBuffer::Fill(Vector4 vec) {
    unsigned char cl[4];
    cl[0] = static_cast<unsigned char>(vec.x * 255);
    cl[1] = static_cast<unsigned char>(vec.y * 255);
    cl[2] = static_cast<unsigned char>(vec.z * 255);
    cl[3] = static_cast<unsigned char>(vec.w * 255);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			depth[i * width + j] = 1.0f;
            for (int k = 0; k < channel; k++) {
                col[(i * width + j) * channel + k] = cl[k];
            }
        }
    }
}
void FrameBuffer::Cover(int x, int y, Vector4 vec) {
	if (x < 0 || x >= width || y < 0 || y >= height) return;
    unsigned char cl[4];
    cl[0] = static_cast<unsigned char>(vec.x * 255);
    cl[1] = static_cast<unsigned char>(vec.y * 255);
    cl[2] = static_cast<unsigned char>(vec.z * 255);
    cl[3] = static_cast<unsigned char>(vec.w * 255);
    for (int k = 0; k < 4; k++) {
        col[(y * width + x) * 4 + k] = cl[k];
    }
}
