#ifndef _EGLRENDERER_H_
#define _EGLRENDERER_H_

#include "GLRenderer.h"

class Android;

class EGLRenderer : public GLRenderer
{
private:
    EGLDisplay  _display;
    EGLSurface  _renderSurface;
    EGLContext	_context;
 
    virtual void EndFrame();
 
public:
    explicit EGLRenderer(unsigned int priority);
    virtual ~EGLRenderer();
 
    virtual bool Init();
    virtual void Destroy();
};

#endif