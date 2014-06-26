#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Kernel* kernel, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    Kernel*         _kernel;
    myGLWidget*     _widgetGL;
};

#endif // MAINWINDOW_H
