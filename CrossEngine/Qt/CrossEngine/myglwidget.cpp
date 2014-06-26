#include "myGLWidget.h"

myGLWidget::myGLWidget(Kernel* kernel, int framesPerSecond, QWidget *parent, char *name)
    : _kernel(kernel), QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }


    _renderer = new QtGLRenderer(2);
    kernel->AddTask(_renderer);
}

void myGLWidget::initializeGL()
{
    _renderer->Init();
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void myGLWidget::resizeGL(int width, int height)
{
    (void)width;
    (void)height;
}

void myGLWidget::paintGL()
{
    _kernel->ExecuteOne();
}

void myGLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}

void myGLWidget::timeOutSlot()
{
}
