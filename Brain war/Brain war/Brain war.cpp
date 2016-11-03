// Brain war.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Brain war.h"
#include <time.h>
#include <sstream>
#include <iomanip>

using namespace std;
#define COUNT_DOWN_TIME 5
#define TIMER_SECOND 1
#define MAX_LOADSTRING 100
#define GAME_OVER 9999
#define BTN_1 1000
#define BTN_2 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwnd;

HWND hTextFormula;
HWND hTextScore;
HWND hBTNResult1;
HWND hBTNResult2;
HWND hCountdown;
int iNum1, iNum2;
int iRightBtn; //0 || 1
int iScore = -1;
float fResult;
WCHAR iCalculus;// addition,  subtraction, multiplication, division
int iTotalTime = COUNT_DOWN_TIME;
wstringstream ssTemp;

//Prototype
int NewGame(HWND hWnd);
int GameInitialize(HWND hWnd);
int GameOver(HWND hWnd);

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BRAINWAR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRAINWAR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRAINWAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BRAINWAR);
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
      CW_USEDEFAULT, 0, 750, 650, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   srand(time(NULL));

   return TRUE;
}

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
	//ssTemp.str(L"");

	////Countdown
	//time(&timer);
	//ssTemp << iBeginTime + COUNT_DOWN_TIME - timer;
	//SetWindowText(hCountdown, ssTemp.str().c_str());
	//UpdateWindow(hWnd);
    switch (message)
    { 
	case WM_CREATE:
	{
		MessageBox(hWnd, L"Chose right answer IN TIME!\nREADY?", L"", MB_OK);;
		GameInitialize(hWnd);
		NewGame(hWnd);
		break;
	}
	case WM_TIMER:
	{
		ssTemp.str(L"");
		iTotalTime--;
		ssTemp << L"Countdown:  " << iTotalTime;
		SetWindowText(hCountdown, ssTemp.str().c_str());
		if (iTotalTime <= 0)
		{
			GameOver(hWnd);
		}
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BTN_1:
			{
				if (0 == iRightBtn)
				{
					NewGame(hWnd);
				}
				else
				{
					GameOver(hWnd);
				}
				break;
			}
			case BTN_2:
			{
				if (1 == iRightBtn)
				{
					NewGame(hWnd);
				}
				else
				{
					GameOver(hWnd);
				}
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

int NewGame(HWND hWnd)
{
	//WCHAR wScore[500];
	iScore += 100;
	//_itow_s(iScore, wScore, 10);
	ssTemp.str(L"");
	ssTemp << L"Your Score: "<< iScore;
	SetWindowText(hTextScore, ssTemp.str().c_str());
	iNum1 = rand() % 500 + 1;
	iNum2 = rand() % 500 + 1;

	int iDiceRoll = rand() % 4 + 1;//random a formular
	if (1 == iDiceRoll)
	{
		iCalculus = L'+';
		fResult = iNum1 + iNum2;
	}
	if (2 == iDiceRoll)
	{
		iCalculus = L'-';
		fResult = iNum1 - iNum2;
	}
	if (3 == iDiceRoll)
	{
		iCalculus = L'*';
		fResult = iNum1 * iNum2;
	}
	if (4 == iDiceRoll)
	{
		iCalculus = L'/';
		fResult = (float)iNum1 / iNum2;
	}
	
	WCHAR wcTemp[255];
	wsprintf(wcTemp, L"%d %c %d = ?", iNum1, iCalculus, iNum2);
	SetWindowText(hTextFormula, wcTemp);

	
	//chose randomly a button to show right answer
	wstringstream ssTemp;
	ssTemp << fResult;
	if (0 == rand() % 2)
	{
		iRightBtn = 0;
	}
	else
	{
		iRightBtn = 1;
	}

	//show right answer
	if (0 == iRightBtn)
	{
		SetWindowText(hBTNResult1, ssTemp.str().c_str());
	}
	else
	{
		SetWindowText(hBTNResult2, ssTemp.str().c_str());
	}

	ssTemp.str(L"");
	if (0 == rand() % 2)//create randomly a wrong answer
	{
		ssTemp << fResult + (rand() % 10 + 1);
	}
	else
	{
		ssTemp << fResult - (rand() % 10 + 1);
	}
	//show wrong answer
	if (0 == iRightBtn)
	{
		SetWindowText(hBTNResult2, ssTemp.str().c_str());
	}
	else
	{
		SetWindowText(hBTNResult1, ssTemp.str().c_str());
	}

	//Countdown
	ssTemp.str(L"");
	ssTemp << L"Countdown:  " << COUNT_DOWN_TIME;
	SetWindowText(hCountdown, ssTemp.str().c_str());
	iTotalTime = COUNT_DOWN_TIME;

	SetTimer(hWnd, TIMER_SECOND, 1000, NULL);


	return 0;
}

int GameInitialize(HWND hWnd)
{
	iScore = -100;
	
	HWND hTextGameTitle = CreateWindowEx(0, L"Static", L"BRAIN WAR", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 50, 650, 60, hWnd, NULL, hInst, NULL);
	hTextFormula = CreateWindowEx(0, L"Static", L"Formula", WS_VISIBLE | WS_CHILD | BS_CENTER | SS_CENTER | WS_BORDER, 50, 150, 650, 40, hWnd, NULL, hInst, NULL);
	hCountdown = CreateWindowEx(0, L"Static", L"Time!", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 250, 650, 40, hWnd, NULL, hInst, NULL);
	hBTNResult1 = CreateWindowEx(0, L"Button", L"123213", WS_VISIBLE | WS_CHILD, 50, 300, 250, 100, hWnd, (HMENU)BTN_1, hInst, NULL);
	hBTNResult2 = CreateWindowEx(0, L"Button", L"123123", WS_VISIBLE | WS_CHILD, 450, 300, 250, 100, hWnd, (HMENU)BTN_2, hInst, NULL);
	hTextScore = CreateWindowEx(0, L"Static", L"Score:", WS_VISIBLE | WS_CHILD | BS_CENTER | SS_CENTER, 50, 450, 650, 40, hWnd, NULL, hInst, NULL);


	//set font
	HFONT hFont = CreateFont(52, 0, 0, 0, 1500, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(hTextGameTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
	hFont = CreateFont(32, 0, 0, 0, 1500, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(hTextFormula, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hBTNResult1, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hBTNResult2, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hTextScore, WM_SETFONT, (WPARAM)hFont, TRUE);
	hFont = CreateFont(22, 0, 0, 0, 1500, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(hCountdown, WM_SETFONT, (WPARAM)hFont, TRUE);


	return 0;
}

int GameOver(HWND hWnd)
{
	int iMessageID;
	KillTimer(hWnd, TIMER_SECOND);
	ssTemp.str(L"");
	ssTemp << L"YOU LOSE, keep going!\nYour score: " << iScore << endl;
	iMessageID = MessageBox(hWnd, ssTemp.str().c_str(), L"You Lose!", MB_RETRYCANCEL);
	
	iScore = -100;
	if (4 == iMessageID)//Press Try again button
	{
		NewGame(hWnd);
	}
	else
	{
		DestroyWindow(hWnd);//Quit
	}

	return 0;
}