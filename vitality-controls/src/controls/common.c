#include "../include/common.h"

/**
* 函数描述：
*	创建并初始化一个编辑器。
*
* 参数：
*	parent: 新创建的编辑器的父窗体。
*
* 返回值：
*	如果创建控件成功，返回该控件的句柄，否则返回 NULL 并设置错误码。
*	错误码可以通过 GetLastError() 获取。
*/
VIC_API HWND Vic_CreateEditor(
	HWND parent
) {
	RECT rect = { 0 };

	if (!GetClientRect(parent, &rect)) {
		return NULL;
	}

	return CreateWindowEx(
		0,
		EDITOR_CLASS_NAME,
		L"",
		WS_CHILD | WS_VISIBLE | ES_MULTILINE |
		WS_VSCROLL | WS_HSCROLL |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0,
		rect.right,
		rect.bottom,
		parent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
}

LRESULT CALLBACK TextEditorWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		TextOut(hdc, 0, 0, L"HELLO", 5);

		EndPaint(hwnd, &ps);
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}