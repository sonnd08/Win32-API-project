// Finalcial manager.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//My global variable

MANAGER Manager;
WCHAR *wcListExpense;
HWND hEditAmount;
HWND hCBCategory;
HWND hEditDescription;
HWND hListExpense;
HWND hEditExpense;
HWND hBtnAdd;
HWND hBtnClear;
HWND htxtTotalExpense;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//My prototype
int OnCreate(HWND hWnd);
int OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void redrawChart(HWND hWnd);


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
    LoadStringW(hInstance, IDC_FINALCIALMANAGER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINALCIALMANAGER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINALCIALMANAGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW );
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINALCIALMANAGER);
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
      CW_USEDEFAULT, 0, 1200, 700, nullptr, nullptr, hInstance, nullptr);

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
		OnCreate(hWnd);
		break;
	}
    case WM_COMMAND:
    {
		OnCommand(hWnd, message, wParam, lParam);
		break;
    }
        break;
    case WM_PAINT:
        {
			OnPaint(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:

		Manager.saveData(FILE_PATH);

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



int OnCreate(HWND hWnd)
{
	InitCommonControls();
	wcListExpense = new WCHAR;

	//text
	HWND txtTitle = CreateWindowEx(0, L"Static", L"FINANCIAL MANAGER", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 30, 1100, 60, hWnd, NULL, hInst, NULL);
	//HWND txtgGroupAdd = CreateWindowEx(0, L"Static", L"Add an expense:", WS_CHILD | WS_VISIBLE, 50, 100, 200, 20, hWnd, NULL, hInst, NULL);
	HWND txtGroupList = CreateWindowEx(0, L"Static", L"Expenses list:", WS_CHILD | WS_VISIBLE, 500, 100, 200, 20, hWnd, NULL, hInst, NULL);

	HWND txtAmount = CreateWindowEx(0, L"Static", L"Amount: ", WS_CHILD | WS_VISIBLE , 50, 120, 150, 20, hWnd, NULL, hInst, NULL);
	HWND txtCategory = CreateWindowEx(0, L"Static", L"Category: ", WS_CHILD | WS_VISIBLE , 50, 170, 150, 20, hWnd, NULL, hInst, NULL);
	HWND txtDescription = CreateWindowEx(0, L"Static", L"Description: ", WS_CHILD | WS_VISIBLE, 50, 220, 150, 20, hWnd, NULL, hInst, NULL);
	htxtTotalExpense = CreateWindowEx(0, L"Static", L"Total Expense: ", WS_CHILD | WS_VISIBLE, 50, 380, 900, 30, hWnd, NULL, hInst, NULL);

	//others
	hEditAmount = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_AUTOHSCROLL, 160, 120, 300, 25, hWnd, NULL, hInst, NULL);
	hCBCategory = CreateWindowEx(0, L"ComboBox", L"", WS_CHILD | WS_VISIBLE | WS_BORDER |CBS_DROPDOWN | CBS_AUTOHSCROLL | CBN_SELCHANGE, 160, 170, 300, 40, hWnd, NULL, hInst, NULL);
	hEditDescription = CreateWindowEx(0, L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 160, 220, 300, 25, hWnd, NULL, hInst, NULL);

	//hListExpense = CreateWindowEx(0, WC_LISTVIEW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT, 500, 100, 550, 200, hWnd, NULL, hInst, NULL);
	hEditExpense = CreateWindowEx(0, L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL|WS_HSCROLL | ES_MULTILINE, 500, 120, 650, 200, hWnd, NULL, hInst, NULL);
	hBtnAdd = CreateWindowEx(0, L"Button", L"ADD", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 270, 190, 50, hWnd, (HMENU)IDC_BTN_ADD, hInst, NULL);
	hBtnClear = CreateWindowEx(0, L"Button", L"CLEAR DATA", WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 270, 180, 50, hWnd, (HMENU)IDC_BTN_CLEAR, hInst, NULL);

	//Set font
	HFONT hFont = CreateFont(35, 0, 0, 0, 1500, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(txtTitle, WM_SETFONT, (WPARAM)hFont, TRUE);

	hFont = CreateFont(17, 0, 0, 0, 500, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(txtAmount, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(txtCategory, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(txtDescription, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hEditAmount, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hCBCategory, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hEditDescription, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hEditExpense, WM_SETFONT, (WPARAM)hFont, TRUE);

	hFont = CreateFont(20, 0, 0, 0, 600, FALSE, TRUE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(htxtTotalExpense, WM_SETFONT, (WPARAM)hFont, TRUE);
	
	hFont = CreateFont(20, 0, 0, 0, 800, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));
	SendMessage(hBtnAdd, WM_SETFONT, (WPARAM)hFont, TRUE);

	//Add value to combobox
	for (int i = 0; i < CATEGORY_ELEMENTS; i++)
	{
		SendMessage(hCBCategory, CB_ADDSTRING, 0, (LPARAM)Manager.wcCategoryList[i]);
	}

	//load data from file
	Manager.loadData(FILE_PATH);
	Manager.reloadExpenseList(hEditExpense, htxtTotalExpense);

	return 0;
}

int OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	// Parse the menu selections:
	switch (wmId)
	{

	case IDC_BTN_ADD:
	{
		//collect information
		WCHAR wcAmount[MAX_LOADSTRING];
		WCHAR wcCategory[MAX_LOADSTRING];
		WCHAR wcDescription[MAX_LOADSTRING];
		GetWindowText(hEditAmount, wcAmount, MAX_LOADSTRING);
		GetWindowText(hCBCategory, wcCategory, MAX_LOADSTRING);
		GetWindowText(hEditDescription, wcDescription, MAX_LOADSTRING);

		//add
		int ErrorCode = Manager.addAnExpense(wcstod(wcAmount, NULL), wcCategory, wcDescription);
		if (ErrorCode == 0)//adding Successfully
		{
			//then update expenses list
			Manager.addLastExpenseToList(hEditExpense, htxtTotalExpense);

			redrawChart(hWnd);

			SetWindowText(hEditAmount, L"");
			SetWindowText(hEditDescription, L"");
		}
		else
		{
			if (ErrorCode == 1)
			{
				MessageBox(hWnd, L"- Amount of money must be greater than zero!\n- Category must not be empty", L"Input error!", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"Too large amount of money ", L"Overflow error!", MB_OK);
			}
		}
		;


		
		break;
	}
	case IDC_BTN_CLEAR:
	{
		Manager.clearData(FILE_PATH, hEditExpense, htxtTotalExpense);
		redrawChart(hWnd);
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
	return 0;
}

int OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code that uses hdc here...

	HPEN hPen = CreatePen(PS_DASHDOT, 3, RGB(255, 255, 255));
	SelectObject(hdc, hPen);

	//DestroyWindow(hwndText);
	//SetParent(hwndText, hWnd);
	HFONT hFont = CreateFont(16, 0, 0, 0, 550, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Courier New"));

	Manager.drawChart(hWnd, hFont, hdc, 100, 430, 400, 20, 10);

	DeleteObject(hPen);


	EndPaint(hWnd, &ps);
	return 0;
}

void redrawChart(HWND hWnd)
{
	//define chart area to redraw
	RECT RedrawArea = Manager.createRect(100, 430, 500, 800);

	InvalidateRect(hWnd, &RedrawArea, TRUE);
}




