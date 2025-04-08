#include "renderroute.h"
RenderRoute::RenderRoute(int w, int h, QObject* parent)
    : QObject(parent), width(w), height(h), channel(4)
{
    stopped = false;
    pipeline = new Pipeline(width, height);
}

void RenderRoute::stopIt() {
    stopped = true;
}

void RenderRoute::loop()
{
    pipeline->initialize();
    Vector3D v1(100, 100, 0), v2(1200, 200, 0), v3(500, 700, 0);
    Mesh* msh = new Mesh();
    msh->triangle(v1, v2, v3);
    pipeline->setVertexBuffer(msh->vertices);
    pipeline->setIndexBuffer(msh->index);
    while (!stopped)
    {
        pipeline->clearBuffer(Vector4D(0, 0, 0, 1.0f));
        pipeline->drawIndex(Pipeline::Fill);
        pipeline->swapBuffer();
        emit frameOut(pipeline->output());
    }
}