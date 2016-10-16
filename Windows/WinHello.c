//+---------------------------------------------------------------------------
//
//  HELLO_WIN.C - Windows GUI 'Hello World!' Example
//
//+---------------------------------------------------------------------------

#include <windows.h>

#define APPNAME TEXT("HELLO_WIN")


LPCWSTR szAppName = APPNAME; // The name of this application
LPCWSTR szTitle = APPNAME; // The title bar text
LPCWSTR pWindowText;

void CenterWindow(HWND hWnd);

//+---------------------------------------------------------------------------
//
//  Function:   WndProc
//
//  Synopsis:   very unusual type of function - gets called by system to
//              process windows messages.
//
//  Arguments:  same as always.
//----------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

		// ----------------------- first and last
	case WM_CREATE:
		CenterWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// ----------------------- get out of it...
	case WM_RBUTTONUP:
		DestroyWindow(hwnd);
		break;

	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
			DestroyWindow(hwnd);
		break;

		// ----------------------- display our minimal info
	case WM_PAINT:
	{
		// Paint SomeThing
		PAINTSTRUCT ps;
		HDC         hdc;
		RECT        rc;
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rc);

		SetTextColor(hdc, RGB(240, 240, 96));
		SetBkMode(hdc, TRANSPARENT);

		DrawText(hdc, TEXT("Hello,Windows"), -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		EndPaint(hwnd, &ps);
		break;
	}

	// ----------------------- let windows do all other stuff
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

// 定时器回调函数

void CALLBACK OnTimer(HWND hwnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{

	// 重绘窗口
	// RedrawWindow(hwnd,NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

//+---------------------------------------------------------------------------
//
//  Function:   WinMain
//
//  Synopsis:   standard entrypoint for GUI Win32 apps
//
//----------------------------------------------------------------------------
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, // 命令行参数
	int nCmdShow
)
{
	MSG msg;
	WNDCLASS wc;
	HWND hwnd;

	// pWindowText = lpCmdLine[0] ? lpCmdLine : "Hello Windows!";

	pWindowText = TEXT("Hello,Windows");

	// Fill in window class structure with parameters that describe
	// the main window.

	ZeroMemory(&wc, sizeof wc);
	wc.hInstance = hInstance;
	wc.lpszClassName = szAppName;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (FALSE == RegisterClass(&wc))
		return 0;

	// create the browser
	hwnd = CreateWindow(
		szAppName,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		360,//CW_USEDEFAULT,
		240,//CW_USEDEFAULT,
		0,
		0,
		hInstance,
		0);

	if (NULL == hwnd)
		return 0;

	// 定时器, (窗口句柄，定时器ID，时间间隔ms，回调函数)
	// SetTimer(hwnd, 0, 1000 / 30, OnTimer);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//+---------------------------------------------------------------------------

//+---------------------------------------------------------------------------

void CenterWindow(HWND hwnd_self)
{
	HWND hwnd_parent;
	RECT rw_self, rc_parent, rw_parent;
	int xpos, ypos;

	hwnd_parent = GetParent(hwnd_self);
	if (NULL == hwnd_parent)
		hwnd_parent = GetDesktopWindow();

	GetWindowRect(hwnd_parent, &rw_parent);
	GetClientRect(hwnd_parent, &rc_parent);
	GetWindowRect(hwnd_self, &rw_self);

	xpos = rw_parent.left + (rc_parent.right + rw_self.left - rw_self.right) / 2;
	ypos = rw_parent.top + (rc_parent.bottom + rw_self.top - rw_self.bottom) / 2;

	SetWindowPos(
		hwnd_self, NULL,
		xpos, ypos, 0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE
	);
}

//+---------------------------------------------------------------------------
