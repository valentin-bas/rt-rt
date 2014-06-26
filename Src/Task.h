#ifndef _TASK_H_
#define _TASK_H_

#include "Base.h"

class Task
{
private:
    unsigned int  _priority;
    bool          _canKill;

protected:
	bool		  _displayable;
    
public:
    explicit Task(unsigned int priority) :
		_priority(priority), _canKill(false),
		_displayable(false) {}
    virtual ~Task() {}
    
    virtual bool	Start()  = 0;
    virtual void	OnSuspend() = 0;
    virtual void	Update() = 0;
    virtual void	OnResume() = 0;
    virtual void	Stop()  = 0;
 
    void	SetCanKill(bool canKill) { _canKill = canKill; }
    bool	CanKill()   { return _canKill; }
    unsigned int Priority()   { return _priority; }
	bool	Displayable() { return _displayable; }
};

#endif