#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cocos2d.h>
#include <gd.h>
#include <MinHook.h>
#include <mutex>

#define WIN32CAC_ENTRY(inject) \
	DWORD WINAPI _thread__func_(void* hModule) { \
        MH_Initialize(); \
	    inject(); \
	    return true; \
	} \
	BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) { \
	    if (reason == DLL_PROCESS_ATTACH) { \
	        CreateThread(0, 0x100, _thread__func_, handle, 0, 0); \
	    } \
	    return TRUE; \
	} 