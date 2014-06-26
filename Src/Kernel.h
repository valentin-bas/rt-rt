#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <list>
#include "Base.h"

class Task;
class Renderer;

class Kernel
{
private:
    typedef std::list<Task*>   TaskList;
 
    TaskList	_tasks;
    TaskList	_pausedTasks;
	Renderer*	_renderer;
 
public:
    Kernel();
    virtual ~Kernel();
 
    void Execute();
    void ExecuteOne();
 
    bool AddTask(Task* task);
    void SuspendTask(Task* task);
    void ResumeTask(Task* task);
    void RemoveTask(Task* task);
    void KillAllTasks();
	void SetRenderer(Renderer* renderer);
};

#endif
