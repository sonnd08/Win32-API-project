// JARS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "JARS.h"
#include <string>
#include <sstream>
#include <iomanip>
#define MAX_LOADSTRING 100
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
using namespace std;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool CALLBACK SetFont(HWND child, LPARAM font) {
	SendMessage(child, WM_SETFONT, font, true);
	return true;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JARS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JARS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JARS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW );
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JARS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

double dIncome;
HWND hEdtIncome;
HWND hEdtNecessity;
HWND hEdtFinancialFree;
HWND hEdtEducation;
HWND hEdtLongtermSaving;
HWND hEdtGive;
HWND hBtnCal;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{

		HWND hStaticText;
		HFONT hFont = CreateFont(22, 0, 0, 0, 1500, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));

		//Static text
		hStaticText = CreateWindowEx(0, L"Static", L"JARS System of Money Management Calculator", WS_CHILD | WS_VISIBLE | BS_CENTER, 50, 20, 500, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);

		hFont = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
		hStaticText = CreateWindowEx(0, L"Static", L"Your income:", WS_CHILD | WS_VISIBLE , 50, 100, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStaticText = CreateWindowEx(0, L"Static", L"Necessity (55%):", WS_CHILD | WS_VISIBLE, 50, 200, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStaticText = CreateWindowEx(0, L"Static", L"Financial freedom (10%):", WS_CHILD | WS_VISIBLE, 50, 250, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStaticText = CreateWindowEx(0, L"Static", L"Education (10%):", WS_CHILD | WS_VISIBLE, 50, 300, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStaticText = CreateWindowEx(0, L"Static", L"Long-term saving for spending (10%):", WS_CHILD | WS_VISIBLE, 50, 350, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStaticText = CreateWindowEx(0, L"Static", L"Give (5%):", WS_CHILD | WS_VISIBLE, 50, 400, 150, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		//SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
		//EditBox
		hEdtIncome = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER , 150, 100, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtIncome, WM_SETFONT, (WPARAM)hFont, TRUE);

		hEdtNecessity = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 250, 200, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtNecessity, WM_SETFONT, (WPARAM)hFont, TRUE);

		hEdtFinancialFree = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 250, 250, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtFinancialFree, WM_SETFONT, (WPARAM)hFont, TRUE);

		hEdtEducation = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 250, 300, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtEducation, WM_SETFONT, (WPARAM)hFont, TRUE);

		hEdtLongtermSaving = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 250, 350, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtLongtermSaving, WM_SETFONT, (WPARAM)hFont, TRUE);

		hEdtGive = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 250, 400, 300, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hEdtGive, WM_SETFONT, (WPARAM)hFont, TRUE);

		//Button
		hBtnCal = CreateWindowEx(0, L"Button", L"CAL", WS_CHILD | WS_VISIBLE, 500, 100, 50, 40, hWnd, (HMENU) BTN_CALCULATE, hInst, NULL);
		SendMessage(hBtnCal, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hBtnCal, WM_SETFOCUS, 1, FALSE);
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BTN_CALCULATE:
			{
				wstringstream ssResult;
				wchar_t *wcString = new wchar_t;
				int iLength = GetWindowTextLength(hEdtIncome);
				GetWindowText(hEdtIncome, wcString, iLength + 1);
				dIncome = wcstold(wcString, NULL);
				//MessageBox(hWnd, wcString, L"", MB_OK);

				ssResult << fixed << setprecision(0) << dIncome*0.55 << '\0';
				SetWindowText(hEdtNecessity, ssResult.str().c_str());

				ssResult.str(L"");
				ssResult << fixed << setprecision(0) << dIncome*0.1 << '\0';
				SetWindowText(hEdtFinancialFree, ssResult.str().c_str());

				ssResult.str(L"");
				ssResult << fixed << setprecision(0) << dIncome*0.1 << '\0';
				SetWindowText(hEdtEducation, ssResult.str().c_str());

				ssResult.str(L"");
				ssResult << fixed << setprecision(0) << dIncome*0.1 << '\0';
				SetWindowText(hEdtLongtermSaving, ssResult.str().c_str());

				ssResult.str(L"");
				ssResult << fixed << setprecision(0) << dIncome*0.05 << '\0';
				SetWindowText(hEdtGive, ssResult.str().c_str());

			
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
