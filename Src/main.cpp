#include "Kernel.h"

#if PLATFORM_WINDOWS



#ifdef QTWINDOWS

#include "../CrossEngine/Qt/CrossEngine/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    Kernel			kernel;

    QApplication app(argc, argv);
    MainWindow  window(&kernel);
    window.show();
    return app.exec();
}

#else

#include "GLFWRenderer.h"
#include "Window.h"
#include "Raytracer.h"

int main(int argc, char* argv[])
{
    Kernel			kernel;
    GLFWRenderer*	renderer;
    Window*			window;

    renderer = new GLFWRenderer(4242);
    kernel.AddTask(renderer);
	kernel.SetRenderer(renderer);
    window = new Window(renderer, 1);
    kernel.AddTask(window);
	kernel.AddTask(new Raytracer(renderer, 3));
    kernel.Execute();
    kernel.KillAllTasks();
}

#endif

#elif PLATFORM_ANDROID

#include <jni.h>
#include <android_native_app_glue.h>
#include "Android.h"
#include "EGLRenderer.h"
#include "AndroidBuf.h"
#include <iostream>

void android_main(struct android_app* state)
{
	Kernel			kernel;
	EGLRenderer*	renderer;
	Android*		android;

	std::cout.rdbuf(new androidbuf);
	app_dummy();
	renderer = new EGLRenderer(2);
	android = new Android(state, renderer, 1);
	kernel.AddTask(android);
	kernel.AddTask(renderer);
	kernel.Execute();
	kernel.KillAllTasks();
}

#else

#error ("Unsupported platform")

#endif
