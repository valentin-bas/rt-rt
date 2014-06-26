#include "Android.h"

static void android_handle_cmd(struct android_app* app, int cmd)
{
	Renderer* pRenderer = static_cast<Renderer*>(app->userData);
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		pRenderer->Init();
		break;
	case APP_CMD_DESTROY:
		pRenderer->Destroy();
		break;
	case APP_CMD_TERM_WINDOW:
		pRenderer->Destroy();
		break;
	case APP_CMD_RESUME:
		break;
	case APP_CMD_PAUSE:
		break;
	}
}

Android::Android(android_app* state, Renderer* renderer, unsigned int priority) :
	Task(priority)
{
    _state = state;
	_renderer = renderer;
    _state->onAppCmd = android_handle_cmd;
    _state->userData = (void*)renderer;
}

Android::~Android(void)
{
}

bool
Android::Start()
{
	return true;
}

void
Android::OnSuspend()
{
}

void
Android::Update()
{
	int events;
	struct android_poll_source* pSource;

	int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
	if (ident >= 0)
	{
		if (pSource)
		{
			pSource->process(_state, pSource);
		}

		if (_state->destroyRequested)
			SetCanKill(true);
	}
}

void
Android::OnResume()
{
}

void
Android::Stop()
{
	_renderer->Destroy();
}