#include "EGLRenderer.h"
#include "Android.h"

EGLRenderer::EGLRenderer(unsigned int priority) :
	GLRenderer(priority), _display(EGL_NO_DISPLAY),
	_renderSurface(EGL_NO_SURFACE), _context(EGL_NO_CONTEXT)
{
}

EGLRenderer::~EGLRenderer()
{
}
#include <iostream>
bool
EGLRenderer::Init()
{
	std::cout << "Init" << std::endl;
    if (_display == EGL_NO_DISPLAY)
    {
		std::cout << "eglGetDisplay" << std::endl;
		_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (!_display)
			return false;
		std::cout << "eglInitialize" << std::endl;
		EGLBoolean res = eglInitialize(_display, NULL, NULL);
		if (!res)
			return false;
		const EGLint RGBX_8888_ATTRIBS[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
		};
		
		const EGLint RGB_565_ATTRIBS[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT, EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6,
			EGL_RED_SIZE, 5, EGL_DEPTH_SIZE, 8, EGL_NONE
		};
		
		const EGLint* attribList;
		
		Android& android = Android::GetSingleton();
		int windowFormat = ANativeWindow_getFormat(android.GetAppState()->window);
		if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888))
		{
			attribList = RGBX_8888_ATTRIBS;
		}
		else
		{
			attribList = RGB_565_ATTRIBS;
		}
		EGLConfig config;
		EGLint numConfigs;
		std::cout << "eglChooseConfig" << std::endl;
		res = eglChooseConfig(_display, attribList, &config, 1, &numConfigs);
		if (!res)
			return false;
		
		EGLint format;
		std::cout << "eglGetConfigAttrib" << std::endl;
		res = eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);
		if (!res)
			return false;
		std::cout << "ANativeWindow_setBuffersGeometry" << std::endl;
		int32_t setBufRes = ANativeWindow_setBuffersGeometry(android.GetAppState()->window, 0, 0, format);
		if (setBufRes != 0)
			return false;
		
		EGLNativeWindowType windowType;
		std::cout << "eglCreateWindowSurface" << std::endl;
		_renderSurface = eglCreateWindowSurface(_display, config, android.GetAppState()->window, NULL);
		if (_renderSurface == EGL_NO_SURFACE)
			return false;
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		std::cout << "eglCreateContext" << std::endl;
		_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, contextAttribs);
		if (_context == EGL_NO_CONTEXT)
			return false;
		std::cout << "eglMakeCurrent" << std::endl;
		res = eglMakeCurrent(_display, _renderSurface, _renderSurface, _context);
		if (!res)
			return false;
		EGLint temp = _width;
		std::cout << "eglQuerySurface EGL_WIDTH" << std::endl;
		res = eglQuerySurface(_display, _renderSurface, EGL_WIDTH, &temp);
		if (!res)
			return false;
		temp = _height;
		std::cout << "eglQuerySurface EGL_HEIGHT" << std::endl;
		res = eglQuerySurface(_display, _renderSurface, EGL_HEIGHT, &temp);
		if (!res)
			return false;
		
		_initialized = true;
		std::cout << "_initialized" << std::endl;
    }
	std::cout << "EndInit" << std::endl;
}

void EGLRenderer::Destroy()
{
    if (_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(_display, _context);
        }
        if (_renderSurface != EGL_NO_SURFACE)
        {
            eglDestroySurface(_display, _renderSurface);
        }
        eglTerminate(_display);
    }
    _display = EGL_NO_DISPLAY;
    _context = EGL_NO_CONTEXT;
    _renderSurface = EGL_NO_SURFACE;
    _initialized = false;
}

void
EGLRenderer::EndFrame()
{
    eglSwapBuffers(_display, _renderSurface);
}