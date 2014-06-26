#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Kernel* kernel, QWidget *parent) :
    _kernel(kernel), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _widgetGL = new myGLWidget(kernel, 0, ui->verticalLayoutWidget);
    ui->verticalLayout->addWidget(_widgetGL);
    _widgetGL->show();
}

MainWindow::~MainWindow()
{
    _kernel->KillAllTasks();
    delete ui;
    delete _widgetGL;
}
