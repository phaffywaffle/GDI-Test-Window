#include <windows.h>

static int ScreenWidth;
static int ScreenHeight;
static int WindowWidth;
static int WindowHeight;

static bool Running;

void
err(char* Message, int Code, UINT Behavoir = MB_OK, char* Title = "Error_Placeholder")
{
	MessageBox(0, Message, Title, Behavoir);
	exit(Code);
}

LRESULT CALLBACK
WindowProc(HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	LRESULT Result = 0;
	switch (uMsg)
	{
	case(WM_CLOSE):
	{
		Running = false;
	} break;
	case(WM_PAINT):
	{
		PAINTSTRUCT Paint;
		BeginPaint(hwnd, &Paint);
		HDC DeviceContext = Paint.hdc;

		HBRUSH SolidBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(DeviceContext, SolidBrush);
		Ellipse(DeviceContext, 0, 0, WindowWidth - 1, WindowHeight - 1);
		DeleteObject(SolidBrush);
		
		SolidBrush = CreateSolidBrush(RGB(0, 128, 200));
		SelectObject(DeviceContext, SolidBrush);
		Ellipse(DeviceContext, WindowWidth / 2 - 10, WindowHeight / 2 - 10, WindowWidth / 2 + 10, WindowHeight / 2 + 10);
		DeleteObject(SolidBrush);

		MoveToEx(DeviceContext, 0, 0, 0);
		LineTo(DeviceContext, WindowWidth - 1, WindowHeight - 1);
		MoveToEx(DeviceContext, WindowWidth - 1, 0, 0);
		LineTo(DeviceContext, 0, WindowHeight - 1);

		EndPaint(hwnd, &Paint);
	} break;
	default:
	{
		Result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	};
	}
	return(Result);
}

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	WNDCLASSEX WindowClass = {};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_DROPSHADOW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = hInstance;
	//	WindowClass.hIcon = ;
	//	WindowClass.hCursor = ;
	WindowClass.lpszClassName = "Placeholder_Class_Name";
	if (!RegisterClassEx(&WindowClass)) err("Failed to register window class", -1);

	ScreenWidth = GetSystemMetrics(0);
	ScreenHeight = GetSystemMetrics(1);
	WindowWidth = ScreenWidth / 3;
	WindowHeight = ScreenHeight / 3;
	HWND Window = CreateWindowEx(0, "Placeholder_Class_Name", "Placeholder_Title", WS_POPUP | WS_VISIBLE, WindowWidth, WindowHeight, WindowWidth, WindowHeight, 0, 0, hInstance, 0);
	if (!Window) err("Failed to create window", -2);

	Running = true;
	MSG Message;
	while (Running)
	{
		while (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
}
