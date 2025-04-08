#pragma once
#include "shader.h"
#include "framebuffer.h"
#include "matrix.h"

class Pipeline
{
private:
    int width, height;
    Shader* m_shader;
    FrameBuffer* m_frontBuffer;
    FrameBuffer* m_backBuffer;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    enum ShadingMode { Simple, Gouraud, Phong };
    enum RenderMode { Wire, Fill };
public:
    Pipeline(int w, int h)
        :width(w), height(h)
        , m_shader(nullptr), m_frontBuffer(nullptr)
        , m_backBuffer(nullptr) {
    }
    ~Pipeline();

    void initialize();
    void clearBuffer(const Vector4D& color, bool depth = false);
    void setVertexBuffer(const std::vector<Vertex>& vertices) { m_vertices = vertices; }
    void setIndexBuffer(const std::vector<unsigned int>& indices) { m_indices = indices; }
    void setShaderMode(ShadingMode mode);
    void drawIndex(RenderMode mode);
    void swapBuffer();
    V2F lerp(const V2F& n1, const V2F& n2, float weight);
    void bresenham(const V2F& from, const V2F& to);
    void scanLinePerRow(const V2F& left, const V2F& right);
    void rasterTopTriangle(V2F& v1, V2F& v2, V2F& v3);
    void rasterBottomTriangle(V2F& v1, V2F& v2, V2F& v3);
    void edgeWalkingFillRasterization(const V2F& v1, const V2F& v2, const V2F& v3);
    unsigned char* output() { return m_frontBuffer->getColorBuffer(); }
};

