#include "GLFWRenderer.h"

GLFWRenderer::GLFWRenderer(unsigned int priority) : GLRenderer(priority)
{
}
 
GLFWRenderer::~GLFWRenderer()
{
}
 
bool
GLFWRenderer::Init()
{
	_width = 645;
	_height = 485;
    if (!glfwInit())
		return false;
    _window = glfwCreateWindow(_width, _height, "CrossEngine", nullptr, nullptr);
	if (!_window)
		return false;
	glfwMakeContextCurrent(_window);
	glewInit();
    _initialized = true;
	return true;
}
 
void
GLFWRenderer::Destroy()
{
    glfwTerminate();
	SetCanKill(true);
}
 
void
GLFWRenderer::EndFrame()
{
    glfwSwapBuffers(_window);
}