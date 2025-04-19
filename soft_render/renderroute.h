#pragma once
#include"QtCore/QObject"
#include "pipeline.h"
#include "maincamera.h"

class RenderRoute :public QObject
{
    Q_OBJECT
public:
    explicit RenderRoute(int w, int h, QObject* parent = nullptr);
    ~RenderRoute() {}
    void stopIt() { stopped = true; }
    void setFpsZero() { fps = 0; }
    int getFps() { return fps; }
signals:
    void frameOut(unsigned char* image);

public slots:
    void loop();
    void loop_3d();
    void loop_scene();
    void loop_model();
    void loop_light();

private:
    bool stopped;
    int width, height, channel;
	int fps;
    Pipeline* pipeline;
};

