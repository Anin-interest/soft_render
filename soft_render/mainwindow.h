#pragma once

#include "Qtwidgets/qmainwindow"
#include "RenderRoute.h"
#include "QtCore/QThread"
#include "QtGui/QImage"

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

private:
    Ui::MainWindow* ui;
	RenderRoute* loop;
	QThread* loopThread;
    QImage* canvas;
};
