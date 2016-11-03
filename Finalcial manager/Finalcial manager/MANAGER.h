#pragma once
#include "stdafx.h"
#include "Expense.h"
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <codecvt>

using namespace std;
#include <windows.h>


class MANAGER
{
private:
	vector<EXPENSE> listExpense;
	struct CHART_HWND
	{
		HWND htxtCategory[CATEGORY_ELEMENTS];
		HWND htxtPercent[CATEGORY_ELEMENTS];
	}chart_HWND ;
public:
	WCHAR wcCategoryList[CATEGORY_ELEMENTS][MAX_LOADSTRING] = { L"Ăn uống", L"Di chuyển (bus, xăng, taxi…)", L"Nhà cửa (tiền thuê nhà, nước, điện,…)",
		L"Xe cộ (xăng, vá xe, bảo dưỡng…)", L"Nhu yếu phẩm (xà bông, sữa tắm…)", L"Dịch vụ (intenet, thẻ cào điện thoại…)" };

	MANAGER()
	{
	}

	~MANAGER()
	{
	}

	//------------------------------------------------------------------------

	int addAnExpense(EXPENSE expense)
	{
		listExpense.push_back(expense);
		return 0;
	}

	//return 1: wrong input
	//return 2: overflow
	int addAnExpense(long double amount, wchar_t *category, wchar_t *description)
	{
		if (wcscmp(category, L"") == 0 | amount == 0)
		{
			MessageBeep(MB_ICONERROR);
			return 1;
		}
		if (amount < 0)
		{
			MessageBeep(MB_ICONERROR);
			return 2;
		}
		EXPENSE *expense = new EXPENSE(amount, category, description);
		listExpense.push_back(*expense);

		return 0;
	}
	
	int addLastExpenseToList(HWND editExpensesList, HWND txtTotal)
	{
		//update expenses list
		wstringstream wssTail;
		int last = listExpense.size()-1;
		if (last < 0)//empty list
		{
			return 1;
		}

		if (last > 0)
		{
			wssTail << "\r\n";
		}
		wssTail << fixed << setprecision(0) << listExpense[last].getAmount() << "\t\t";
		wssTail << listExpense[last].getCategory() << "\t\t";
		wssTail << listExpense[last].getDescription() << '\0';


		int TextLen = SendMessage(editExpensesList, WM_GETTEXTLENGTH, 0, 0);
		SendMessage(editExpensesList, EM_SETSEL, TextLen, TextLen);
		SendMessage(editExpensesList, EM_REPLACESEL, FALSE, (LPARAM)wssTail.str().c_str());

		wstringstream ss;
		ss.imbue(std::locale("vit"));
		ss << "Total Expense: " << fixed << setprecision(0) << std::showbase << std::put_money(TotalExpense())._Val;
		//update total expense
		SetWindowText(txtTotal, ss.str().c_str());
	}

	//call this to reload all data of expense list (data from vector)
	int reloadExpenseList(HWND editExpensesList, HWND txtTotal)
	{
		SendMessage(editExpensesList, WM_SETTEXT, NULL, (LPARAM)L"");
		SendMessage(txtTotal, WM_SETTEXT, NULL, (LPARAM)L"Total Expense: 0");

		for (int i = 0; i < listExpense.size(); i++)
		{
			//update expenses list
			wstringstream wssTail;
			if (i != 0)
			{
				wssTail << "\r\n";
			}
			wssTail << fixed << setprecision(0) << listExpense[i].getAmount() << "\t\t";
			wssTail << listExpense[i].getCategory() << "\t\t";
			wssTail << listExpense[i].getDescription() << '\0';


			int TextLen = SendMessage(editExpensesList, WM_GETTEXTLENGTH, 0, 0);
			SendMessage(editExpensesList, EM_SETSEL, TextLen, TextLen);
			SendMessage(editExpensesList, EM_REPLACESEL, FALSE, (LPARAM)wssTail.str().c_str());

			wstringstream ss;
			ss.imbue(std::locale("vit"));
			ss << "Total Expense: " << fixed << setprecision(0) << std::showbase << std::put_money(TotalExpense())._Val;
			//update total expense
			SetWindowText(txtTotal, ss.str().c_str());
		}
		return 0;
	}

	long double TotalExpense()
	{
		long double *result = new long double;
		*result = 0;
		for (int i = 0; i < listExpense.size(); i++)
		{
			*result += listExpense[i].getAmount();
		}

		return *result;
	}

	//to vector
	int loadData(char *filePath)
	{
		wfstream fileIn;
		fileIn.open(filePath);
		if (!fileIn.is_open())
		{
			return 0;
		}
		fileIn.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wstring wsAmount, wsCategory, wsDescription;
		while (getline(fileIn, wsAmount, L'\t'))
		{
			
			getline(fileIn, wsCategory, L'\t');
			getline(fileIn, wsDescription);


			addAnExpense(wcstold(wsAmount.c_str(), NULL), (wchar_t*)wsCategory.c_str(), (wchar_t*)wsDescription.c_str());
		}
		fileIn.close();
		return 0;
	}

	int saveData(char *filePath)
	{
		wfstream fileOut;
		fileOut.open(filePath, ios::out | ios::trunc);
		fileOut.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

		//begin save
		for (int i = 0; i < listExpense.size(); i++)
		{
			wstringstream wss;
			wss << fixed << setprecision(0) << listExpense[i].getAmount() << "\t" << listExpense[i].getCategory() << "\t" << listExpense[i].getDescription();
			if (i != listExpense.size() - 1)
			{
				wss << endl;
			}
			fileOut << wss.str();
		}

		fileOut.close();
		return 0;
	}

	int clearData(char *filePath, HWND editExpensesList, HWND txtTotal)
	{

		listExpense.clear();
		saveData(filePath);
		reloadExpenseList(editExpensesList, txtTotal);
		return 0;
	}
	
	int drawChart(HWND hWnd, HFONT hFont, HDC hdc, int xTop, int yTop, int fullBarWidth, int barHeight, int distance)
	{
		
		int i = 0;
		int txtBoxWidth = 400;
		int yText = yTop;
		int yBar = yTop;
		int xBar = xTop + txtBoxWidth + 10;
		int realBarWidth = 0;

		int Red = 230, Green = 200, Blue = 75;
		HBRUSH hbrush = CreateSolidBrush(RGB(Red, Green, Blue));

		//txtBoxWidth -= 70;// for percent text
		
		//begin draw chart
		wstringstream wss;
		wss.imbue(locale(""));
		do
		{
			float per = percentOf(wcCategoryList[i]);
			realBarWidth = fullBarWidth*per + 3;//i want draw a line even if percent = 0

			drawBar(hdc, xBar, yBar, realBarWidth, barHeight, hbrush);
			
			//write text
			wss.str(L"");//clear stream
			if (chart_HWND.htxtCategory[i] == NULL)
			{
				wss << wcCategoryList[i] << ":\0";
				chart_HWND.htxtCategory[i] = CreateWindowEx(0, L"Static", wss.str().c_str(), WS_VISIBLE | WS_CHILD, xTop, yBar, txtBoxWidth, barHeight, hWnd, NULL, NULL, NULL);
			
			}
			
			wss.str(L"");
			wss << " " << put_money(TotalOf(wcCategoryList[i]))._Val <<"("<< fixed << setprecision(0) << per*100 << "%)\0";
			if (chart_HWND.htxtPercent[i] == NULL)
			{
				chart_HWND.htxtPercent[i] = CreateWindowEx(0, L"Static", wss.str().c_str(), WS_VISIBLE | WS_CHILD, xBar + realBarWidth, yBar, txtBoxWidth, barHeight, hWnd, NULL, NULL, NULL);
			}
			else
			{
				DestroyWindow(chart_HWND.htxtPercent[i]);
				chart_HWND.htxtPercent[i] = CreateWindowEx(0, L"Static", wss.str().c_str(), WS_VISIBLE | WS_CHILD, xBar + realBarWidth, yBar, txtBoxWidth, barHeight, hWnd, NULL, NULL, NULL);
				//SetWindowText(chart_HWND.htxtPercent[i], wss.str().c_str());
			}
			//setfont
			SendMessage(chart_HWND.htxtCategory[i], WM_SETFONT, (WPARAM)hFont, TRUE);
			SendMessage(chart_HWND.htxtPercent[i], WM_SETFONT, (WPARAM)hFont, TRUE);

			//generate new brush color for next bar
			Red -= 0;
			Green -= 25;
			Blue -= 10;
			hbrush = CreateSolidBrush(RGB(Red, Green, Blue));

			yText += barHeight + distance;
			yBar += barHeight + distance;
			i++;
		} while (i < CATEGORY_ELEMENTS);

		return 0;
	}

	int drawBar(HDC hdc, int x, int y, int width, int height, HBRUSH hbrush)
	{
		RECT rect = createRect(x, y, x + width, y + height);
		FillRect(hdc, &rect, hbrush);

		return 0;
	}

	float percentOf(WCHAR *category)
	{
		if (TotalExpense() == 0)
		{
			return 0;
		}

		long double sum = TotalOf(category);

		float result = sum*1.0/ TotalExpense();
		return  result;
	}

	long double TotalOf(WCHAR *category)
	{
		long double sum = 0;
		for (int i = 0; i < listExpense.size(); i++)
		{
			if (!wcscmp(category, listExpense[i].getCategory()))
			{
				sum += listExpense[i].getAmount();
			}
		}
		return sum;
	}

	static RECT createRect(LONG left, LONG top, LONG right, LONG bottom)
	{
		RECT rect;
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;

		return rect;
	}

};

