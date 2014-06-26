#ifndef _ANDROID_H_
#define _ANDROID_H_

#include "Task.h"
#include "Renderer.h"
#include "Singleton.h"
#include <jni.h>
#include <android_native_app_glue.h>

class EGLRenderer;

class Android : public Task, public Singleton<Android>
{
private:
	android_app*	_state;
	Renderer*		_renderer;

public:
	Android(android_app* pState, Renderer* renderer, unsigned int priority);
	virtual ~Android();

	android_app* GetAppState() { return _state; }

	virtual bool	Start();
	virtual void	OnSuspend();
	virtual void	Update();
	virtual void	OnResume();
	virtual void	Stop();
};

#endif