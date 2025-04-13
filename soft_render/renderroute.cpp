#include "renderroute.h"
#include "include.h"

RenderRoute::RenderRoute(int w, int h, QObject* parent)
    : QObject(parent), width(w), height(h), channel(4)
{
	fps = 0;
    stopped = false;
    pipeline = new Pipeline(width, height);
}

void RenderRoute::loop()
{
    pipeline->initialize();
    Vector3 v1(0, 0.8, 0), v2(-0.5, -0.5, 0), v3(0.5, -0.5, 0);

    maincamera* camera = new maincamera();
    Mesh* msh = new Mesh();
    msh->triangle(v1, v2, v3);
    pipeline->setVertexBuffer(msh->vertices);
    pipeline->setIndicesBuffer(msh->indices);
    while (!stopped)
    {
        pipeline->clearBuffer(Vector4(0.502f, 0.698f, 0.800f, 1.0f));
        pipeline->drawIndex(Pipeline::Fill);
        pipeline->swapBuffer();
        emit frameOut(pipeline->output());
        fps++;
        //camera->rotateY(0.01f);
    }
}

void RenderRoute::loop_3d()
{
    pipeline->initialize();
	QString path = "./res/temp.png";
	int tex0id = pipeline->genTexture(path);
    Vector4 pos(0.f, 0.f, 0.f, 0.0f);
    maincamera* camera = new maincamera();
    Mesh* msh = new Mesh();
	//msh->asBox(3.0f, 3.0f, 3.0f);
    //msh->cube(.4f, .4f, .4f, 0, pos);
	msh->pyramid();
    pipeline->setVertexBuffer(msh->vertices);
    pipeline->setIndicesBuffer(msh->indices);
    while (!stopped)
    {
        pipeline->clearBuffer(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
        pipeline->drawIndex(Pipeline::Fill, camera);
        pipeline->swapBuffer();
        emit frameOut(pipeline->output());
        camera->rotateY(1);
		fps++;
    }
}