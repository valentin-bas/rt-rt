#include "Renderer.h"
#include "DisplayableTask.h"

Renderer::Renderer(unsigned int priority) :
	_initialized(false), Task(priority)
{
}
 
Renderer::~Renderer()
{
}
 
bool
Renderer::Start()
{
    return true;
}
 
void
Renderer::Update()
{
    if (_initialized)
    {
        RenderFrame();
    }
}
 
void
Renderer::RenderFrame()
{
	DisplayableTaskList::iterator it;

    BeginFrame();
	for(it = _displayableTasks.begin() ; it != _displayableTasks.end() ; ++it)
    {
        DisplayableTask* t = *it;
		t->Display();
	}
    EndFrame();
}

bool
Renderer::AddDisplayableTask(DisplayableTask* task)
{
	if (task == nullptr)
		return false;
	try { _displayableTasks.insert(_displayableTasks.end(), task); }
	catch (std::bad_alloc) { return false; }
	return true;
}

void
Renderer::RemoveDisplayableTask(DisplayableTask* task)
{
	_displayableTasks.remove(task);
}