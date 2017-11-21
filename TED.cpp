#include "stdafx.h"
#include "TED.h"


#define MAX_LOADSTRING 100
#define ID_TIMER 101

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
TEDController controller;
UINT TimmerID = 0;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TED));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PEN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TED);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_PEN));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	TimmerID = SetTimer(hWnd, ID_TIMER, 700, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		controller = TEDController();
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		controller.windowUpdate(hWnd);
		EndPaint(hWnd, &ps);
	}

	case WM_KEYDOWN:
	{
		if (wParam == VK_RIGHT)
		{
			controller.moveCursor(controller.RIGHT, hWnd); 
			break;
		}

		if (wParam == VK_LEFT)
		{
			controller.moveCursor(controller.LEFT, hWnd);
			break;
		}

		if (wParam == VK_UP)
		{
			controller.moveCursor(controller.UP, hWnd);
			break;
		}

		if (wParam == VK_DOWN)
		{
			controller.moveCursor(controller.DOWN, hWnd);
			break;
		}

		if (wParam == VK_HOME)
		{
			controller.handleKey(controller.HOME, hWnd);
			break;
		}

		if (wParam == VK_END)
		{
			controller.handleKey(controller.END, hWnd);
			break;
		}

		if (wParam == VK_DELETE)
		{
			controller.handleKey(controller.DEL, hWnd);
			break;
		}
		break;
	}
	case WM_CHAR:
	{
		if (wParam == VK_RETURN)
		{
			controller.handleInsertSymbol(hWnd, wParam);
			break;
		}

		if (wParam == VK_TAB)
		{
			break;
		}

		if (wParam == VK_ESCAPE)
		{
			break;
		}

		if (wParam == VK_BACK)
		{
			controller.handleKey(controller.BACKSPASE, hWnd);
			break;
		}
		controller.handleInsertSymbol(hWnd, wParam);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		controller.handleMouseClick(LOWORD(lParam) / 20, HIWORD(lParam) / 20, hWnd);
		break;
	}
	case WM_TIMER:
	{
		controller.cursorTimer(hWnd);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


