// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		//TextOut(h_dc, 10, 10, L"Hello", 5);

		SetBkMode(h_dc, TRANSPARENT);
		SetTextColor(h_dc, RGB(0, 100, 200));
		wchar_t str[64];
		int len;
		for (int step = 2; step <= 9; step++) {
			for (int i = 1; i <= 9; i++) {
				len = wsprintf(str, L"%d * %d = %d", step, i, step * i);
				TextOut(h_dc, 10 + (step - 1) * 100, 100 + i * 20, str, len);
			}
		}

		HFONT h_font = CreateFont(32, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY
		,DEFAULT_PITCH | FF_SWISS, L"굴림체");
		HGDIOBJ h_old_font = SelectObject(h_dc, h_font);
		TextOut(h_dc, 10, 10, L"구구단", 3);

		RECT r = { 10, 10, 830, 70 };
		FillRect(h_dc, &r, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
		DrawText(h_dc, L"구구단", 3, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		// 문자열 정렬에 좋음

		SelectObject(h_dc, h_old_font);
		DeleteObject(h_font);
		EndPaint(hWnd, &ps);
		return 0;
	}
	
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}