#include "GLRenderer.h"

GLRenderer::GLRenderer(int priority) :
	Renderer(priority)
{
}
 
GLRenderer::~GLRenderer()
{
}
 
void
GLRenderer::BeginFrame()
{
	float ratio;

	ratio = _width / (float) _height;
	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}
 
void
GLRenderer::EndFrame()
{
}
