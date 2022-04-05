#pragma once

#ifdef VITALITY_CONTROLS_EXPORTS
#define VIC_API __declspec(dllexport)
#else
#define VIC_API __declspec(dllimport)
#endif // VITALITY_CONTROLS_EXPORTS

#include <Windows.h>

/**
* 函数描述：
*	初始化编辑器环境，需要在调用任何本程序集的函数之前，
*	调用本函数。
* 
* 返回值：
*	如果初始化成功，返回 TRUE，否则返回 FALSE，并设置错误码，
*	错误码可以通过 GetLastError() 获取。
*/
VIC_API BOOL Vic_Init();

/**
* 函数描述：
*	创建并初始化一个编辑器。
* 
* 参数：
*	parent: 新创建的编辑器的父窗体。
* 
* 返回值：
*	如果创建控件成功，返回该控件的句柄，否则返回 -1 并设置错误码。
*	错误码可以通过 GetLastError() 获取。
*/
VIC_API HWND Vic_CreateEditor(
	HWND parent
);

