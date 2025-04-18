#pragma once
#include "baseshader.h"
#include "light.h"
#include "framebuffer.h"
#include "maincamera.h"
#include "matrix.h"
#include "directlight.h"
#include "pointlight.h"
#include "spotlight.h"


class Pipeline
{
private:
    int width, height;
    BaseShader* m_shader;
    FrameBuffer* m_frontBuffer;
    FrameBuffer* m_backBuffer;
	Matrix viewPortMatrix;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    enum ShadingMode { Simple, Phong };
    enum RenderMode { Wire, Fill };
public:
    Pipeline(int w, int h) :width(w), height(h), m_shader(nullptr),
        m_frontBuffer(nullptr), m_backBuffer(nullptr) {
    }
    ~Pipeline();

    void initialize();
    void clearBuffer(const Vector4& color, float depth = 1.0f);
    void setVertexBuffer(const std::vector<Vertex>& vertices) { m_vertices = vertices; }
    void setIndicesBuffer(const std::vector<unsigned int>& indices) { m_indices = indices; }
    void setShaderMode(ShadingMode mode);
    void drawIndex(RenderMode mode);
    void drawIndex(RenderMode mode, maincamera* camera);
    void swapBuffer();
    void perspective(V2F& target);

    bool lineCliping(const V2F& from, const V2F& to);
    bool backFaceCulling(RenderMode mode, Vector3 pos, const Vector4& v1, const Vector4& v2, const Vector4& v3);

    void bresenham(const V2F& from, const V2F& to);
    void scanLinePerRow(const V2F& left, const V2F& right);
    void rasterTopTriangle(V2F& v1, V2F& v2, V2F& v3);
    void rasterBottomTriangle(V2F& v1, V2F& v2, V2F& v3);
    void edgeWalkingFillRasterization(const V2F& v1, const V2F& v2, const V2F& v3);

    unsigned char* output() { return m_frontBuffer->getColorBuffer(); }

	int genTexture(QString& path) { return m_shader->genTexture(path); }
	void setTextureID(int id) { m_shader->setTextureID(id); }
    void setMaterial(Material* m) { m_shader->setMaterial(m); }
    void setLight(Light* l) { m_shader->setLight(l); }
};

