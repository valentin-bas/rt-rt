#include "Kernel.h"
#include "Task.h"
#include "DisplayableTask.h"
#include "Renderer.h"

Kernel::Kernel(void) :
	_renderer(nullptr)
{
}


Kernel::~Kernel(void)
{
}

void
Kernel::Execute()
{
	while(_tasks.size())
	{
        ExecuteOne();
	}
}

void
Kernel::ExecuteOne()
{
    TaskList::iterator it;
    for(it = _tasks.begin() ; it != _tasks.end() ;)
    {
        Task* t = *it;
        it++;
        if (!t->CanKill())
            t->Update();
    }
    for(it = _tasks.begin() ; it != _tasks.end() ;)
    {
        Task *t = *it;
        it++;
        if(t->CanKill())
        {
            t->Stop();
            _tasks.remove(t);
            delete t;
        }
    }
}

bool
Kernel::AddTask(Task* task)
{
	if(!task->Start())
		return false;

	TaskList::iterator it;
	for(it = _tasks.begin() ; it != _tasks.end() ; it++)
	{
		if((*it)->Priority() > task->Priority())
			break;
	}
	try { _tasks.insert(it, task); }
	catch (std::bad_alloc) { return false; }
	if (_renderer && task->Displayable() &&
		_renderer->AddDisplayableTask(dynamic_cast<DisplayableTask*>(task)))
		return false;
	return true;
}

void
Kernel::SuspendTask(Task* task)
{
	if(std::find(_tasks.begin(), _tasks.end(), task) != _tasks.end())
	{
		task->OnSuspend();
		_tasks.remove(task);
		_pausedTasks.push_back(task);
	}
}

void
Kernel::ResumeTask(Task* task)
{
	if(std::find(_pausedTasks.begin(), _pausedTasks.end(), task) != _pausedTasks.end())
	{
		task->OnResume();
		_pausedTasks.remove(task);
		TaskList::iterator it;
		for(it = _tasks.begin() ; it != _tasks.end() ; it++)
		{
			if((*it)->Priority() > task->Priority())
				break;
		}
		_tasks.insert(it, task);
	}
}

void
Kernel::RemoveTask(Task* task)
{
	if(std::find(_pausedTasks.begin(), _pausedTasks.end(), task) != _pausedTasks.end())
	{
		task->SetCanKill(true);
		if (_renderer && task->Displayable())
			_renderer->RemoveDisplayableTask(dynamic_cast<DisplayableTask*>(task));
	}
}

void
Kernel::KillAllTasks()
{
	TaskList::iterator it;
	for(it = _tasks.begin() ; it != _tasks.end() ; it++)
	{
		(*it)->SetCanKill(true);
	}
	for(it = _pausedTasks.begin() ; it != _pausedTasks.end() ; it++)
	{
		(*it)->SetCanKill(true);
	}
}

void
Kernel::SetRenderer(Renderer* renderer)
{
	_renderer = renderer;
}