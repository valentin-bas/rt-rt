#ifndef _QTGLRENDERER_H_
#define _QTGLRENDERER_H_

#include "GLRenderer.h"

class QtGLRenderer : public GLRenderer
{
private:
    virtual void EndFrame();

public:
    explicit QtGLRenderer(unsigned int priority);
    virtual ~QtGLRenderer();
 
    virtual bool Init();
    virtual void Destroy();
};

#endif
