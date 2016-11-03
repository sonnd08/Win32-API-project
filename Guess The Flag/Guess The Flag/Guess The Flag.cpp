// Guess The Flag.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Guess The Flag.h"
#include <Windows.h>
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_LOADSTRING 100
#define FLAG_PATH "Flags Bitmap/"
#define INI_PATH L"config.ini"
#define MAX_BUFFER_SIZE 300

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


HBITMAP hbmpFlag;
HWND hwButton_1;
HWND hwButton_2;
HWND hwCorrectAnswer;
HWND hwScore;

int iFirstFlag;
int iSecondFlag;
int iMainFlag;
int iScore = 0;
wstring wTemp;
LPCWSTR FlagPath;

vector<string> vecFlagsName({ "Afghanistan", "Albania", "Algeria", "American_Samoa", "Andorra", "Angola", "Anguilla",  "Antigua_and_Barbuda", "Argentina", "Armenia"});
//,
//"Aruba", "Australia", "Austria", "Vietnam", "United_Kingdom", "United_States_of_America", "Uruguay", "Venezuela", "Zimbabwe", "Turkey",
//"Tunisia", "Syria", "Thailand", "Taiwan", "Sweden", "Somalia", "Singapore", "Saudi_Arabia", "Romania", "Republic_of_the_Congo", "Philippines",
//"Laos", "Malaysia", "Macao", "Italy", "Iran", "Israel", "Indonesia", "Japan", "India", "Iceland", "Germany", "Cambodia", "China", "France", "Finland"

int dice_roll;  // to generate randomly numbers

//Personal prototype
LPCWSTR StringToWchar_t(string String);
int NewGame();//return correct flag pos
bool isBmpLoaded(HBITMAP hbitmap);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUESSTHEFLAG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESSTHEFLAG));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESSTHEFLAG));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUESSTHEFLAG);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   WCHAR *wTempValue = new WCHAR;
   WCHAR wCurrFilePath[255];

   //wCurrFilePath = (WCHAR*)L"E:/Visual Studio 2013/Projects/16-17/Guess The Flag/Guess The Flag/config.ini";
   int iWidth;
   int iHeight;

   GetCurrentDirectory(MAX_BUFFER_SIZE, wCurrFilePath);
   wcscat_s(wCurrFilePath, L"\\config.ini");
   
   GetPrivateProfileString(L"app", L"WIDTH", L"980", wTempValue, MAX_BUFFER_SIZE, wCurrFilePath);
   iWidth = _wtoi(wTempValue);
   GetPrivateProfileString(L"app", L"HEIGHT", L"500", wTempValue, MAX_BUFFER_SIZE, wCurrFilePath);
   iHeight = _wtoi(wTempValue);

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, iWidth, iHeight, NULL, NULL, hInstance, NULL);
   //MessageBox(hWnd, wCurrFilePath, L"", MB_OK);
   _itow_s(iWidth, wCurrFilePath, 10);
   //MessageBox(hWnd, wCurrFilePath, L"", MB_OK);
   //delete[]wTempValue;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
	{

					  srand(time(NULL));
					  //hwndPlayingScene = CreateWindowEx(0, L"Static", L"2", WS_CHILD | WS_VISIBLE, 0, 0, 1000, 1000, hWnd, NULL, hInst, NULL);
					  //CreateWindowEx(0, L"Static", L"2", WS_CHILD | WS_VISIBLE, 0, 0, 1000, 1000, hWnd, NULL, NULL, NULL);

					  //handler for 2 flag bitmaps
					  hwButton_1 = CreateWindowEx(0, L"Button", L"Flag 1", WS_CHILD | WS_VISIBLE | BS_BITMAP, 50, 50, 300, 200, hWnd, (HMENU)1000, hInst, NULL);
					  hwButton_2 = CreateWindowEx(0, L"Button", L"Flag 2", WS_CHILD | WS_VISIBLE | BS_BITMAP, 600, 50, 300, 200, hWnd, (HMENU)1001, hInst, NULL);
					  hwCorrectAnswer = CreateWindowEx(0, L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 370, 100, 200, 220, hWnd, NULL, NULL, NULL);
					  hwScore = CreateWindowEx(0, L"Static", L"score", WS_CHILD | WS_VISIBLE | SS_CENTER, 370, 400, 200, 220, hWnd, NULL, NULL, NULL);
					  NewGame();
					  break;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 1000:
		{
					 if ((HWND)lParam == hwButton_1 && iMainFlag == iFirstFlag)
					 {
						 MessageBox(hWnd, L"AWESOME, you're correct!", L"Caption", MB_OK);
						 iScore += 100;

					 }
					 else
					 {
						 MessageBox(hWnd, L"Oh nooo, you're WRONG!", L"Caption", MB_OK);
						 iScore -= 100;
					 }

					 NewGame();
					 break;
		}
		case 1001:
		{
					 if ((HWND)lParam == hwButton_2 && iMainFlag == iSecondFlag)
					 {
						 MessageBox(hWnd, L"AWESOME, you're correct!", L"Caption", MB_OK);
						 iScore += 100;
					 }
					 else
					 {
						 MessageBox(hWnd, L"Oh nooo, you're WRONG!", L"Caption", MB_OK);
						 iScore -= 100;
					 }

					 NewGame();
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
	{

		RECT rect;
		int iWidth;
		int iHeight;
		if (GetWindowRect(hWnd, &rect))
		{
			iWidth = rect.right - rect.left;
			iHeight = rect.bottom - rect.top;
		}

		WCHAR wCurrFilePath[MAX_BUFFER_SIZE];
		WCHAR *wString = new WCHAR[MAX_BUFFER_SIZE];
		//wCurrFilePath = (WCHAR*)L"E:/Visual Studio 2013/Projects/16-17/Guess The Flag/Guess The Flag/config.ini";

		GetCurrentDirectory(MAX_BUFFER_SIZE, wCurrFilePath);
		wcscat_s(wCurrFilePath, L"\\config.ini");
		_itow_s(iWidth, wString, MAX_BUFFER_SIZE, 10);
		WritePrivateProfileString(L"app", L"WIDTH", wString, wCurrFilePath);
		_itow_s(iHeight, wString, MAX_BUFFER_SIZE, 10);
		WritePrivateProfileString(L"app", L"HEIGHT", wString, wCurrFilePath);

		PostQuitMessage(0);
		break;
	}
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


LPCWSTR StringToWchar_t(string String)
{
	wTemp = wstring(String.begin(), String.end());
	return wTemp.c_str();
}

int NewGame()//return correct flag pos
{
	dice_roll = rand() % vecFlagsName.size();//to indentify a random flag

	//draw randomly first flag
	iFirstFlag = dice_roll;
	FlagPath = StringToWchar_t(FLAG_PATH + vecFlagsName[dice_roll] + ".bmp");
	hbmpFlag = (HBITMAP)LoadImage(NULL, FlagPath, IMAGE_BITMAP, 300, 200, LR_LOADFROMFILE);
	SendMessage(hwButton_1, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmpFlag);

	//draw randomly second flag
	while (dice_roll == iFirstFlag)//to sure 2 bitmap is diff
	{
		dice_roll = rand() % vecFlagsName.size();
	}
	iSecondFlag = dice_roll;
	FlagPath = StringToWchar_t(FLAG_PATH + vecFlagsName[dice_roll] + ".bmp");
	hbmpFlag = (HBITMAP)LoadImage(NULL, FlagPath, IMAGE_BITMAP, 300, 200, LR_LOADFROMFILE);
	SendMessage(hwButton_2, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmpFlag);
	//STM_SETIMAGE for static style
	//show name of country(random from 2 country above)
	if (rand() % 2 == 0)
	{
		iMainFlag = iFirstFlag;
	}
	else
	{
		iMainFlag = iSecondFlag;
	}
	SetWindowText(hwCorrectAnswer, StringToWchar_t(vecFlagsName[iMainFlag]));
	SetWindowText(hwScore, StringToWchar_t("SCORE: " + to_string(iScore)));
	return -1;
}

bool isBmpLoaded(HBITMAP hbitmap)
{
	return hbitmap != NULL;
}
