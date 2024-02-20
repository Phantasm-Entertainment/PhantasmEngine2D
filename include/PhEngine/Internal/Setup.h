#ifndef PHENGINE_INTERNAL_SETUP_H_
#define PHENGINE_INTERNAL_SETUP_H_

#ifdef _MSC_VER
#ifdef PHENGINE_BUILDING_DLL
#define PHENGINE_EXPORT __declspec(dllexport)
#else
#define PHENGINE_EXPORT __declspec(dllimport)
#endif
#else
#define PHENGINE_EXPORT
#endif

#define PHENGINE_NAMESPACE PhEngine
#define PHENGINE_GRAPHICS_NAMESPACE PHENGINE_NAMESPACE::Graphics
#define PHENGINE_MATH_NAMESPACE PHENGINE_NAMESPACE::Math

#endif