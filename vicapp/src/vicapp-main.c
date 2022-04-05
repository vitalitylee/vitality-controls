#include <Windows.h>
#include "../../shared-include/vitality-controls.h"

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

PCWSTR MAIN_CLASS_NAME = L"VIC-APP-MAIN";

HWND editorHwnd = NULL;

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE: {
		editorHwnd = Vic_CreateEditor(hwnd);
		if (editorHwnd == 0) {
			int lastError = GetLastError();
			ShowWindow(hwnd, 0);
		}
		return 0;
	}
	case WM_SIZE: {
		RECT rect = { 0 };
		if (!GetWindowRect(hwnd, &rect)) {
			break;
		}
		MoveWindow(
			editorHwnd,
			0,
			0,
			rect.right,
			rect.bottom,
			TRUE
		);
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL InitApplication(HINSTANCE hinstance)
{
	WNDCLASSEX wcx = { 0 };

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = MainWindowProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hinstance;
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = GetStockObject(WHITE_BRUSH);
	wcx.lpszClassName = MAIN_CLASS_NAME;
	wcx.hIconSm = LoadImage(
		hinstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR
	);

	return RegisterClassEx(&wcx);
}

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow)
{
	HWND hwnd = CreateWindowEx(
		0,
		MAIN_CLASS_NAME,
		L"VicApp",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(HWND)NULL,
		(HMENU)NULL,
		hinstance,
		(LPVOID)NULL
	);

	if (!hwnd) {
		return FALSE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	MSG msg = { 0 };

	if (!Vic_Init()) {
		int err = GetLastError();

		return FALSE;
	}

	if (!InitApplication(hInstance))
		return FALSE;

	if (!InitInstance(hInstance, nShowCmd))
		return FALSE;

	BOOL fGotMessage;
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
