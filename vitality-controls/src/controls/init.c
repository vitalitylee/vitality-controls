#include "../include/common.h"

/**
* 函数描述：
*	初始化编辑器环境，需要在调用任何本程序集的函数之前，
*	调用本函数。
*/
VIC_API BOOL Vic_Init() {
	WNDCLASSEX wnd = { 0 };

	wnd.cbSize = sizeof(wnd);
	wnd.hInstance = GetModuleHandle(NULL);
	wnd.lpszClassName = EDITOR_CLASS_NAME;
	wnd.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wnd.hCursor = LoadCursor(NULL, IDC_IBEAM);
	wnd.style = CS_GLOBALCLASS | CS_PARENTDC | CS_DBLCLKS;
	wnd.lpfnWndProc = TextEditorWindowProc;

	return RegisterClassEx(&wnd) != 0;
}