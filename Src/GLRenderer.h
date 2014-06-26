#ifndef _GLRENDERER_H_
#define _GLRENDERER_H_

#include "Renderer.h"

#if PLATFORM_WINDOWS

#ifdef QTWINDOWS
#include <QtOpenGL>
#else
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#endif
#elif PLATFORM_ANDROID
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#error ("Unsupported platform")
#endif

class GLRenderer : public Renderer
{
protected:
	unsigned int _width;
	unsigned int _height;
    virtual void BeginFrame();
    virtual void EndFrame();
 
public:
    explicit GLRenderer(int priority);
    virtual ~GLRenderer();
	unsigned int Width() { return _width; }
	unsigned int Height() { return _height; }
};

#endif
