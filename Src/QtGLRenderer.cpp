#include "QtGLRenderer.h"

QtGLRenderer::QtGLRenderer(unsigned int priority) : GLRenderer(priority)
{
}
 
QtGLRenderer::~QtGLRenderer()
{
}
 
bool
QtGLRenderer::Init()
{
	_width = 640;
	_height = 480;
    _initialized = true;
	return true;
}
 
void
QtGLRenderer::Destroy()
{
	SetCanKill(true);
}
 
void
QtGLRenderer::EndFrame()
{
}
