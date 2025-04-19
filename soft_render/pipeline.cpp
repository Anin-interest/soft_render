#include "pipeline.h"
#include "algorithm"
#include "basicshader.h"
#include "lightshader.h"

Pipeline::~Pipeline()
{
    if (m_shader)delete m_shader;
    if (m_frontBuffer)delete m_frontBuffer;
    if (m_backBuffer)delete m_backBuffer;
    m_shader = nullptr;
    m_frontBuffer = nullptr;
    m_backBuffer = nullptr;
}

void Pipeline::initialize()
{
    if (m_frontBuffer != nullptr)delete m_frontBuffer;
    if (m_backBuffer)delete m_backBuffer;
    if (m_shader)delete m_shader;
    viewPortMatrix.viewPort(0, 0, width, height);
    m_frontBuffer = new FrameBuffer(width, height);
    m_backBuffer = new FrameBuffer(width, height);
    m_shader = new BasicShader();
}

void Pipeline::drawIndex(RenderMode mode)
{
    if (m_indices.empty())return;
    for (unsigned int i = 0; i < m_indices.size();) {
        Vertex vv1 = m_vertices[m_indices[i++]], vv2 = m_vertices[m_indices[i++]], vv3 = m_vertices[m_indices[i++]]; // 取出第三个顶点
        V2F v1 = m_shader->vertexShader(vv1), v2 = m_shader->vertexShader(vv2), v3 = m_shader->vertexShader(vv3);
        // cliping
        if (lineCliping(v1, v2) || lineCliping(v1, v3) || lineCliping(v2, v3)) continue;
        // perspective
        perspective(v1);
        perspective(v2);
        perspective(v3);
        // viewport transfer
        v1.posV2P = viewPortMatrix * v1.posV2P;
        v2.posV2P = viewPortMatrix * v2.posV2P;
        v3.posV2P = viewPortMatrix * v3.posV2P;
        /*这部分是光栅化*/
        if (mode == Wire)
        {
            bresenham(v1, v2);
            bresenham(v1, v3);
            bresenham(v2, v3);
        }
        else if (mode == Fill)
        {
            edgeWalkingFillRasterization(v1, v2, v3);
        }
    }
}

void Pipeline::drawIndex(RenderMode mode, maincamera* camera)
{
    if (m_indices.empty())return;
    m_shader->setCam(camera);
    for (unsigned int i = 0; i < m_indices.size();) {
        Vertex vv1 = m_vertices[m_indices[i++]], vv2 = m_vertices[m_indices[i++]], vv3 = m_vertices[m_indices[i++]]; // 取出第三个顶点
        V2F v1 = m_shader->vertexShader(vv1), v2 = m_shader->vertexShader(vv2), v3 = m_shader->vertexShader(vv3);
		// back face culling
		if (!backFaceCulling(mode, camera->pos, v1.posM2W, v2.posM2W, v3.posM2W)) continue;
		// cliping
		if (lineCliping(v1, v2) || lineCliping(v1, v3) || lineCliping(v2, v3)) continue;
		// perspective
		perspective(v1);
		perspective(v2);
		perspective(v3);
        // viewport transfer
        v1.posV2P = viewPortMatrix * v1.posV2P;
        v2.posV2P = viewPortMatrix * v2.posV2P;
        v3.posV2P = viewPortMatrix * v3.posV2P;

        if (mode == Wire)
        {
            bresenham(v1, v2);
            bresenham(v1, v3);
            bresenham(v2, v3);
        }
        else if (mode == Fill)
        {
            edgeWalkingFillRasterization(v1, v2, v3);
        }
    }
}

void Pipeline::setShaderMode(ShadingMode mode)
{
    if (m_shader)delete m_shader;
    if (mode == Simple)
        m_shader = new BasicShader();
    else if (mode == Phong)
        m_shader = new LightShader();
}

void Pipeline::clearBuffer(const Vector4& color, float depth)
{
    m_backBuffer->Fill(color, depth);
}

void Pipeline::swapBuffer()
{
    FrameBuffer* tmp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = tmp;
}

void Pipeline::perspective(V2F& target)
{
	target.posV2P /= target.posV2P.w;
    // map from [-1,1] to [0,1]
    target.posV2P.z = (target.posV2P.z + 1.0f) * 0.5f;
}

bool Pipeline::lineCliping(const V2F& from, const V2F& to)
{
    // return whether the line is totally outside or not.
    float vMin = -from.posV2P.w, vMax = from.posV2P.w;
    float x1 = from.posV2P.x, y1 = from.posV2P.y;
    float x2 = to.posV2P.x, y2 = to.posV2P.y;

    int tmp = 0;
    int outcode1 = 0, outcode2 = 0;

    // outcode1 calculation.
    tmp = (y1 > vMax) ? 1 : 0;
    tmp <<= 3;
    outcode1 |= tmp;
    tmp = (y1 < vMin) ? 1 : 0;
    tmp <<= 2;
    outcode1 |= tmp;
    tmp = (x1 > vMax) ? 1 : 0;
    tmp <<= 1;
    outcode1 |= tmp;
    tmp = (x1 < vMin) ? 1 : 0;
    outcode1 |= tmp;

    // outcode2 calculation.
    tmp = (y2 > vMax) ? 1 : 0;
    tmp <<= 3;
    outcode2 |= tmp;
    tmp = (y2 < vMin) ? 1 : 0;
    tmp <<= 2;
    outcode2 |= tmp;
    tmp = (x2 > vMax) ? 1 : 0;
    tmp <<= 1;
    outcode2 |= tmp;
    tmp = (x2 < vMin) ? 1 : 0;
    outcode2 |= tmp;

    if ((outcode1 & outcode2) != 0)
        return true;

    // bounding box judge.
    Vector2 minPoint, maxPoint;
    minPoint.x = min(from.posV2P.x, to.posV2P.x);
    minPoint.y = min(from.posV2P.y, to.posV2P.y);
    maxPoint.x = max(from.posV2P.x, to.posV2P.x);
    maxPoint.y = max(from.posV2P.y, to.posV2P.y);
    if (minPoint.x > vMax || maxPoint.x < vMin || minPoint.y > vMax || maxPoint.y < vMin)
        return true;

    return false;
}

bool Pipeline::backFaceCulling(RenderMode mode, Vector3 pos, const Vector4& v1, const Vector4& v2, const Vector4& v3)
{
    // back face culling.
    if (mode == RenderMode::Wire)
        return true;
    Vector4 tmp1 = v2 - v1;
    Vector4 tmp2 = v3 - v1;
    Vector3 edge1(tmp1.x, tmp1.y, tmp1.z);
    Vector3 edge2(tmp2.x, tmp2.y, tmp2.z);
    Vector3 viewRay(pos.x - v1.x,
        pos.y - v1.y,
        pos.z - v1.z);
    Vector3 normal = edge1.cross(edge2);
    return normal.dot(viewRay) > 0;
}

#pragma region 光栅化算法
void Pipeline::bresenham(const V2F& from, const V2F& to)
{
    int dx = to.posV2P.x - from.posV2P.x;
    int dy = to.posV2P.y - from.posV2P.y;
    int sx = 1, sy = 1;
    int nowX = from.posV2P.x, nowY = from.posV2P.y;
    if (dx < 0) {
        sx = -1;
        dx = -dx;
    }
    if (dy < 0) {
        sy = -1;
        dy = -dy;
    }

    V2F tmp;
    if (dy <= dx)
    {
        int d = 2 * dy - dx;
        for (int i = 0; i <= dx; ++i)
        {
            tmp = lerp(from, to, static_cast<float>(i) / dx);
            m_backBuffer->Cover(nowX, nowY, m_shader->fragmentShader(tmp));
            nowX += sx;
            if (d <= 0)d += 2 * dy;
            else {
                nowY += sy;
                d += 2 * dy - 2 * dx;
            }
        }
    }
    else
    {
        int d = 2 * dx - dy;
        for (int i = 0; i <= dy; ++i)
        {
            tmp = lerp(from, to, static_cast<float>(i) / dy);
            m_backBuffer->Cover(nowX, nowY, m_shader->fragmentShader(tmp));
            nowY += sy;
            if (d < 0)d += 2 * dx;
            else {
                nowX += sx;
                d -= 2 * dy - 2 * dx;
            }
        }
    }
}

void Pipeline::scanLinePerRow(const V2F& left, const V2F& right)
{
    V2F current;
    int length = right.posV2P.x - left.posV2P.x + 1;
    for (int i = 0; i <= length; ++i)
    {
        // linear interpolation
        float weight = static_cast<float>(i) / length;
        current = lerp(left, right, weight);
        current.posV2P.x = left.posV2P.x + i;
        current.posV2P.y = left.posV2P.y;
		// depth test
		float depth = m_backBuffer->getDepthBuffer(current.posV2P.x,current.posV2P.y);
        if (depth < current.posV2P.z) {
            continue;
        }
		m_backBuffer->setDepthBuffer(current.posV2P.x, current.posV2P.y, current.posV2P.z);

        float w = 1.0 / current.oneDivZ;
        current.texcoord *= w;
        // fragment shader
		m_backBuffer->Cover(current.posV2P.x, current.posV2P.y, m_shader->fragmentShader(current));
    }
}

void Pipeline::rasterTopTriangle(V2F& v1, V2F& v2, V2F& v3)
{
    V2F left = v2;
    V2F right = v3;
    V2F dest = v1;
    V2F tmp, newleft, newright;
    if (left.posV2P.x > right.posV2P.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = left.posV2P.y - dest.posV2P.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posV2P.y = newright.posV2P.y = left.posV2P.y - i;
        scanLinePerRow(newleft, newright);
    }
}

void Pipeline::rasterBottomTriangle(V2F& v1, V2F& v2, V2F& v3)
{
    V2F left = v1;
    V2F right = v2;
    V2F dest = v3;
    V2F tmp, newleft, newright;
    if (left.posV2P.x > right.posV2P.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = dest.posV2P.y - left.posV2P.y + 1;
    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posV2P.y = newright.posV2P.y = left.posV2P.y + i;
        scanLinePerRow(newleft, newright);
    }
}

void Pipeline::edgeWalkingFillRasterization(const V2F& v1, const V2F& v2, const V2F& v3)
{
    V2F tmp;
    V2F target[3] = {v1, v2, v3};
    if (target[0].posV2P.y > target[1].posV2P.y)
    {
        tmp = target[0];
        target[0] = target[1];
        target[1] = tmp;
    }
    if (target[0].posV2P.y > target[2].posV2P.y)
    {
        tmp = target[0];
        target[0] = target[2];
        target[2] = tmp;
    }
    if (target[1].posV2P.y > target[2].posV2P.y)
    {
        tmp = target[1];
        target[1] = target[2];
        target[2] = tmp;
    }
    if (target[0].posV2P.y == target[1].posV2P.y) {
        rasterBottomTriangle(target[0], target[1], target[2]);
    }
    else if (target[1].posV2P.y == target[2].posV2P.y) {
        rasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        float weight = static_cast<float>(target[1].posV2P.y - target[0].posV2P.y) / (target[2].posV2P.y - target[0].posV2P.y);
        V2F newPoint = lerp(target[0], target[2], weight);
        newPoint.posV2P.y = target[1].posV2P.y;
        rasterTopTriangle(target[0], newPoint, target[1]);
        rasterBottomTriangle(newPoint, target[1], target[2]);
    }
}
#pragma endregion