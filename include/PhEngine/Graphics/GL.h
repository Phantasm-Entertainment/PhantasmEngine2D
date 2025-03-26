#ifdef PHENGINE_DEBUG
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#undef GetMessage
#endif
#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif
#include "glad/gl_debug.h"
#else
#include "glad/gl.h"
#endif
#include <SDL3/SDL.h>