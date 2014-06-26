#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include "DisplayableTask.h"
#include "GLRenderer.h"
#include <cuda_runtime.h>

class GLRenderer;

class Raytracer : public DisplayableTask
{
public:
    Raytracer(GLRenderer* renderer, unsigned int priority);
    virtual ~Raytracer();
 
    virtual bool	Start();
    virtual void	OnSuspend() {}
    virtual void	Update();
    virtual void	OnResume() {}
    virtual void	Stop();
	virtual void	Display();
private:
	GLRenderer*		_renderer;
	GLuint			_vbo;
	uchar4*			_buffer;
};

#endif