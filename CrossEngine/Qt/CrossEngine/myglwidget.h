#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include "../../../Src/Kernel.h"
#include "../../../Src/QtGLRenderer.h"

class myGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit myGLWidget(Kernel* kernel, int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void keyPressEvent( QKeyEvent *keyEvent );

public slots:
    virtual void timeOutSlot();

private:
    Kernel*         _kernel;
    QtGLRenderer*	_renderer;
    QTimer*         t_Timer;

};

#endif // MYGLWIDGET_H
