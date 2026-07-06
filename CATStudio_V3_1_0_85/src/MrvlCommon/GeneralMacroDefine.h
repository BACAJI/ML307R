#pragma once

#ifdef _CATCORE_DLL
#define CATCORE_DLLEXPORT __declspec(dllexport)
#else					
#define CATCORE_DLLEXPORT
#endif

#ifdef _CATCORE_DLL
#define CATCORE_DLL_STATIC_EXPORT __declspec(dllexport)
#else			//Modified by hlguo for client import static variables when link to dll.
#define CATCORE_DLL_STATIC_EXPORT __declspec(dllimport)
#endif

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
