#include "Window.h"
#include "GLFWRenderer.h"
#include <GLFW\glfw3.h>
 
Window::Window(GLFWRenderer* renderer, unsigned int priority) : 
	_renderer(renderer), Task(priority)
{
}
 
Window::~Window()
{
}
 
bool
Window::Start()
{
    if (!_renderer->Init())
		return false;
    return true;
}
 
void
Window::OnSuspend()
{
 
}
 
void
Window::Update()
{
	glfwPollEvents();
    if (glfwWindowShouldClose(_renderer->Window()))
		SetCanKill(true);
}
 
void
Window::OnResume()
{
}
 
void
Window::Stop()
{
    _renderer->Destroy();
}