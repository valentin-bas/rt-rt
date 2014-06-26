#ifndef _DISPLAYABLETASK_H_
#define _DISPLAYABLETASK_H_

#include "Task.h"

class DisplayableTask : public Task
{
private:
    unsigned int  _priority;
    bool          _canKill;
    
public:
	DisplayableTask(unsigned int priority) :
		Task(priority) { _displayable = true; }
    virtual ~DisplayableTask() {}
    
    virtual bool	Start()  = 0;
    virtual void	OnSuspend() = 0;
    virtual void	Update() = 0;
    virtual void	OnResume() = 0;
    virtual void	Stop()  = 0;
    virtual void	Display()  = 0;
};

#endif