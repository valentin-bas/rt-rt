#ifndef _GLFWRENDERER_H_
#define _GLFWRENDERER_H_

#include "GLRenderer.h"

struct GLFWwindow;

class GLFWRenderer : public GLRenderer
{
private:
    virtual void EndFrame();

protected:
	GLFWwindow*	_window;
 
public:
    explicit GLFWRenderer(unsigned int priority);
    virtual ~GLFWRenderer();
 
    virtual bool Init();
    virtual void Destroy();

	GLFWwindow*	Window() { return _window; }
};

#endif