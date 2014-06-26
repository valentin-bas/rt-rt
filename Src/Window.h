#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Task.h"

class GLFWRenderer;

class Window : public Task
{
private:
    GLFWRenderer*	_renderer;
	bool			_closing;
 
public:
    Window(GLFWRenderer* renderer, unsigned int priority);
    virtual ~Window();
 
    virtual bool	Start();
    virtual void	OnSuspend();
    virtual void	Update();
    virtual void	OnResume();
    virtual void	Stop();
};

#endif