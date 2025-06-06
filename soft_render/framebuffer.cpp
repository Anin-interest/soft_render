#include "framebuffer.h"

void FrameBuffer::Fill(Vector4 vec, float dep) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			depth[i * width + j] = dep;
            int idx = (i * width + j) * channel;
            col[idx + 0] = static_cast<unsigned char>(vec.x * 255);
            col[idx + 1] = static_cast<unsigned char>(vec.y * 255);
            col[idx + 2] = static_cast<unsigned char>(vec.z * 255);
            col[idx + 3] = static_cast<unsigned char>(vec.w * 255);
        }
    }
}
void FrameBuffer::Cover(int x, int y, Vector4 vec) {
	if (x < 0 || x >= width || y < 0 || y >= height) return;
    int idx = (y * width + x) * channel;
    col[idx + 0] = static_cast<unsigned char>(vec.x * 255);
    col[idx + 1] = static_cast<unsigned char>(vec.y * 255);
    col[idx + 2] = static_cast<unsigned char>(vec.z * 255);
    col[idx + 3] = static_cast<unsigned char>(vec.w * 255);
}
