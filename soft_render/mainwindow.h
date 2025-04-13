#pragma once

#include "Qtwidgets/qmainwindow"
#include "RenderRoute.h"
#include "QtCore/QThread"
#include "QtGui/QImage"
#include "QtCore/QTimer"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent*) override;
    void receiveFrame(unsigned char* data);
    void fpsTimeOut();

private:
    Ui::MainWindow* ui;
    QImage* canvas;
    QTimer* timer;
	RenderRoute* loop;
	QThread* loopThread;
};
