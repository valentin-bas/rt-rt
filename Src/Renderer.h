#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Task.h"

class DisplayableTask;

#include <list>

class Renderer : public Task
{
protected:
	typedef std::list<DisplayableTask*>   DisplayableTaskList;
 
    DisplayableTaskList	_displayableTasks;
    bool				_initialized;
 
    virtual void	RenderFrame();
    virtual void	BeginFrame() = 0;
    virtual void	EndFrame() = 0;
 
public:
    Renderer(unsigned int priority);
    virtual ~Renderer();
 
    virtual bool	Init() = 0;
    virtual void	Destroy() = 0;
 
    virtual bool	Start();
    virtual void	OnSuspend() {}
    virtual void	Update();
    virtual void	OnResume() {}
    virtual void	Stop() {}

	bool AddDisplayableTask(DisplayableTask* task);
	void RemoveDisplayableTask(DisplayableTask* task);
};

#endif