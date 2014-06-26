#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef ANDROID
#define PLATFORM_ANDROID  1
#define PLATFORM_IOS      0
#define PLATFORM_WINDOWS  0
#elif _WIN32
#define PLATFORM_ANDROID  0
#define PLATFORM_IOS      0
#define PLATFORM_WINDOWS  1
#elif IOS
#define PLATFORM_ANDROID  0
#define PLATFORM_IOS      1
#define PLATFORM_WINDOWS  0
#else
//#error "Unsupported platform"
#endif

#endif