#include "renderroute.h"
#include "objmodel.h"


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
        pipeline->clearBuffer(Vector4(0.5f, 0.7f, 0.8f, 1.0f));
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
	QString path = "./res/images/container.jpg";
	int tex0id = pipeline->genTexture(path);
    maincamera* camera = new maincamera();
    Mesh* msh = new Mesh();
    msh->box(0.5f, 0.5f, 0.5f);
	//msh->pyramid();
    pipeline->setVertexBuffer(msh->vertices);
    pipeline->setIndicesBuffer(msh->indices);
    while (!stopped)
    {
        pipeline->clearBuffer(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
		//pipeline->setTextureID(tex0id);
        pipeline->drawIndex(Pipeline::Fill, camera);
		//pipeline->setTextureID(-1);
        pipeline->swapBuffer();
        emit frameOut(pipeline->output());
        camera->rotateY(1);
		fps++;
    }
}

void RenderRoute::loop_scene()
{
	pipeline->initialize();
	QString path0 = "./res/images/container.jpg";
	QString path1 = "./res/images/me.png";
	int tex0id = pipeline->genTexture(path0);
	int tex1id = pipeline->genTexture(path1);
	maincamera* camera = new maincamera();
	Mesh* msh_box1 = new Mesh();
	msh_box1->box(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(0.25, 0, 0));
	Mesh* msh_box2 = new Mesh();
	msh_box2->graybox(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(-0.25, 0, -0.25));
	Mesh* msh_box3 = new Mesh();
	msh_box3->graybox(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(-0.25, 0, 0.25));
	Mesh* msh_face = new Mesh();
	msh_face->face(1.0f, 0.0f, 1.0f, Vector3(0, -1.0f / 6, 0));
	while (!stopped)
	{
		pipeline->clearBuffer(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
	    pipeline->setVertexBuffer(msh_box1->vertices);
	    pipeline->setIndicesBuffer(msh_box1->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setTextureID(tex0id);
		pipeline->setVertexBuffer(msh_box2->vertices);
		pipeline->setIndicesBuffer(msh_box2->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setTextureID(-1);
		pipeline->setVertexBuffer(msh_box3->vertices);
		pipeline->setIndicesBuffer(msh_box3->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setTextureID(tex1id);
		pipeline->setVertexBuffer(msh_face->vertices);
		pipeline->setIndicesBuffer(msh_face->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setTextureID(-1);
		pipeline->swapBuffer();
		emit frameOut(pipeline->output());
		camera->rotateY(1);
		fps++;
	}
}

void RenderRoute::loop_model() {
	pipeline->initialize();
	pipeline->setShaderMode(Pipeline::Phong);
	QString path = "./res/models/boom.obj";
	Material* material = new Material();
	material->setMaterial(Vector3(0.1, 0.1, 0.1), Vector3(0.5, 0.5, 0.5), Vector3(0.5, 0.5, 0.5), 1.0);
	Light* light = new PointLight();
	light->setPointLight(Vector3(), Vector3(), Vector3(1.5, 1.5, 1.5), Vector3(0.0, 0.1f / 3, 0.1f / 3), Vector3(1, 0.7, 1.8));
	//light->setPointLight(Vector3(), Vector3(), Vector3(1.5, 1.5, 1.5), Vector3(0.0, 1.75f, 0.0), Vector3(0.4, 0.01, 0.4));
	pipeline->setMaterial(material);
	pipeline->setLight(light);
	maincamera* camera = new maincamera(Vector3(0.0f, 0.0f, 1.0f), Vector3(), Vector3(0, 1, 0), 15, 8.f / 6, 0, 50);
	//maincamera* camera = new maincamera();
	Mesh* msh = new ObjModel(path);
	pipeline->setVertexBuffer(msh->vertices);
	pipeline->setIndicesBuffer(msh->indices);
	while (!stopped)
	{
		pipeline->clearBuffer(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->swapBuffer();
		emit frameOut(pipeline->output());
		camera->rotateY(3);
		fps++;
	}
}

void RenderRoute::loop_light() {
	pipeline->initialize();
	pipeline->setShaderMode(Pipeline::Phong);
	QString path = "./res/images/container.jpg";
	int tex0id = pipeline->genTexture(path);
	Material* material = new Material();
	material->setMaterial(Vector3(0.1, 0.1, 0.1), Vector3(0.5, 0.5, 0.5), Vector3(0.5, 0.5, 0.5), 0.5);
	Light* light = new DirectLight();
	light->setDirectLight(Vector3(), Vector3(), Vector3(1,1,1), Vector3(1, 0, 0));
	//Light* light = new SpotLight();
	//light->setSpotLight(Vector3(), Vector3(), Vector3(1.5, 1.5, 1.5), 60,
	//	Vector3(0.0, 1.0f / 3, 0), Vector3(0, -1, 0), Vector3(1, 0.7, 1.8));
	//Light* light = new PointLight();
	//light->setPointLight(Vector3(), Vector3(), Vector3(1.5, 1.5, 1.5), Vector3(0.0, -1.0f / 6, 0), Vector3(1, 0.7, 1.8));
	pipeline->setMaterial(material);
	pipeline->setLight(light);
	maincamera* camera = new maincamera();
	Mesh* msh_box1 = new Mesh();
	msh_box1->graybox(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(0.25, 0, 0));
	Mesh* msh_box2 = new Mesh();
	msh_box2->graybox(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(-0.25, 0, -0.25));
	Mesh* msh_box3 = new Mesh();
	msh_box3->graybox(1.0f / 3, 1.0f / 3, 1.0f / 3, Vector3(-0.25, 0, 0.25));
	Mesh* msh_face = new Mesh();
	msh_face->face(1.0f, 0.0f, 1.0f, Vector3(0, -1.0f / 6, 0));
	while (!stopped)
	{
		pipeline->clearBuffer(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
		pipeline->setTextureID(tex0id);
		pipeline->setVertexBuffer(msh_box1->vertices);
		pipeline->setIndicesBuffer(msh_box1->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setVertexBuffer(msh_box2->vertices);
		pipeline->setIndicesBuffer(msh_box2->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setVertexBuffer(msh_box3->vertices);
		pipeline->setIndicesBuffer(msh_box3->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setVertexBuffer(msh_face->vertices);
		pipeline->setIndicesBuffer(msh_face->indices);
		pipeline->drawIndex(Pipeline::Fill, camera);
		pipeline->setTextureID(-1);
		pipeline->swapBuffer();
		emit frameOut(pipeline->output());
		camera->rotateY(1);
		fps++;
	}
}