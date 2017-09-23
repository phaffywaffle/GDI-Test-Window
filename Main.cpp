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

void
PaintTest(HWND hwnd)
{
	
	PAINTSTRUCT Paint;
	BeginPaint(hwnd, &Paint);
	RECT Rect = Paint.rcPaint;
	HDC DeviceContext = Paint.hdc;

	HBRUSH SolidBrush = CreateSolidBrush(RGB(255, 255, 255));
	Rectangle(DeviceContext, Rect.left, Rect.top, Rect.right, Rect.bottom);

	SolidBrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(DeviceContext, SolidBrush);
	Ellipse(DeviceContext, Rect.left, Rect.top, Rect.right, Rect.bottom);
	DeleteObject(SolidBrush);

	SolidBrush = CreateSolidBrush(RGB(0, 128, 200));
	SelectObject(DeviceContext, SolidBrush);
	Ellipse(DeviceContext, Rect.right / 2 - 9, Rect.bottom / 2 - 9, Rect.right / 2 + 10, Rect.bottom / 2 + 10);
	DeleteObject(SolidBrush);

	MoveToEx(DeviceContext, Rect.left, Rect.top, 0);
	LineTo(DeviceContext, Rect.right, Rect.bottom);
	MoveToEx(DeviceContext, Rect.right, Rect.top, 0);
	LineTo(DeviceContext, Rect.left, Rect.bottom);

	MoveToEx(DeviceContext, Rect.right / 2, Rect.top, 0);
	LineTo(DeviceContext, Rect.right / 2, Rect.bottom);
	MoveToEx(DeviceContext, Rect.left, Rect.bottom / 2, 0);
	LineTo(DeviceContext, Rect.right, Rect.bottom / 2);

	EndPaint(hwnd, &Paint);
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
		//PaintTest(hwnd);

		PAINTSTRUCT Paint;
		BeginPaint(hwnd, &Paint);
		RECT Rect = Paint.rcPaint;
		HDC DeviceContext = Paint.hdc;

		HBRUSH SolidBrush = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(DeviceContext, SolidBrush);
		Rectangle(DeviceContext, Rect.left, Rect.top, Rect.right, Rect.bottom);
		DeleteObject(SolidBrush);

		SolidBrush = CreateSolidBrush(RGB(255, 0, 0));
		POINT Points1[] = {{Rect.left, Rect.top},{Rect.left, Rect.bottom / 2},{Rect.right / 2, Rect.top}};
		SelectObject(DeviceContext, SolidBrush);
		Polygon(DeviceContext, Points1, 3);
		
		POINT Points2[] = { { Rect.right / 2, Rect.top },{ Rect.right -1, Rect.bottom/ 2 },{ Rect.right - 1, Rect.top } };
		SelectObject(DeviceContext, SolidBrush);
		Polygon(DeviceContext, Points2, 3);

		POINT Points3[] = { { Rect.right - 1, Rect.bottom / 2},{ Rect.right / 2, Rect.bottom - 1},{ Rect.right - 1, Rect.bottom - 1} };
		SelectObject(DeviceContext, SolidBrush);
		Polygon(DeviceContext, Points3, 3);

		POINT Points4[] = { { Rect.left, Rect.bottom -1 },{ Rect.left, Rect.bottom / 2 },{ Rect.right / 2, Rect.bottom -1} };
		SelectObject(DeviceContext, SolidBrush);
		Polygon(DeviceContext, Points4, 3);
		DeleteObject(SolidBrush);

		EndPaint(hwnd, &Paint);
		
		PaintTest(hwnd);
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
//	WindowClass.style = CS_DROPSHADOW;
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
	HWND Window = CreateWindowEx(WS_EX_LAYERED, "Placeholder_Class_Name", "Placeholder_Title", WS_POPUP | WS_VISIBLE, WindowWidth, WindowHeight, WindowWidth, WindowHeight, 0, 0, hInstance, 0);
	SetLayeredWindowAttributes(Window, RGB(255, 0, 0), 0, LWA_COLORKEY);

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