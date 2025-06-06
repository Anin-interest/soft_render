#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Qtgui/QPainter"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 600);

	timer = new QTime();
    loop = new RenderRoute(width(), height(), nullptr);
    loopThread = new QThread(this);
    loop->moveToThread(loopThread);
    connect(loopThread, &QThread::finished, loop, &RenderRoute::deleteLater);
    connect(loopThread, &QThread::started, loop, &RenderRoute::loop_3d);
    connect(loop, &RenderRoute::frameOut, this, &MainWindow::receiveFrame);
    connect(loop, &RenderRoute::frameOut, this, &MainWindow::fpsTimeOut);
    loopThread->start();
	start = timer->currentTime().msecsSinceStartOfDay();
}

MainWindow::~MainWindow()
{
    delete ui;
    loop->stopIt();
    loopThread->quit();
    loopThread->wait();
    if (canvas)delete canvas;
    if (loopThread)delete loopThread;
    loop = nullptr;
    canvas = nullptr;
    loopThread = nullptr;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if (canvas)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, *canvas);
    }
    QWidget::paintEvent(event);
}

void MainWindow::receiveFrame(unsigned char* data)
{
    if (canvas) delete canvas;
    canvas = new QImage(data, width(), height(), QImage::Format_RGBA8888);
    update();
}

void MainWindow::fpsTimeOut()
{
    end = timer->currentTime().msecsSinceStartOfDay();
	int vertexCount = loop->getVertexCount();
	int faceCount = loop->getFaceCount();
	loop->setVertexCountZero();
	loop->setFaceCountZero();
	if (end - start < 1000) return;
    int fps = 1000.f * loop->getFps() / (end - start);
    loop->setFpsZero();

    this->setWindowTitle(QString("powered by Anin fps: %1 vertexs: %2 triangles: %3").arg(fps).arg(vertexCount).arg(faceCount));
	start = end;
}