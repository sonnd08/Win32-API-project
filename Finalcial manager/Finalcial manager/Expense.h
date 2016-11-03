#pragma once
#include <wchar.h>
#include "stdafx.h"
#define MAX_BUFFER_SIZE 200
#define NORMAL 0;
#define INPUT_ERROR 1
class EXPENSE
{
private:
	long double Amount;
	wchar_t *Category;
	wchar_t *Description;
public:

	EXPENSE()
	{
		Amount = 0;
		Category = new wchar_t[MAX_BUFFER_SIZE];
		Description = new wchar_t[MAX_BUFFER_SIZE];
	}

	EXPENSE(long double amount, wchar_t *category, wchar_t *description)
	{
		Amount = 0;
		Category = new wchar_t[MAX_BUFFER_SIZE];
		Description = new wchar_t[MAX_BUFFER_SIZE];
		Amount = amount;
		setCategory(category);
		setDescription(description);
	}

	~EXPENSE()
	{
	}

	//set values
	int setAmount(long double value)
	{
		if (value <= 0)
		{
			return INPUT_ERROR;
		}
		else
		{
			Amount = value;
		}

		return 0;
	}

	
	//return 1: empty category
	int setCategory(wchar_t * buffer)
	{
		if (wcscmp(buffer, L"") == 0)
		{
			return 1;
		}

		wcscpy_s(Category, wcslen(buffer) + 1, buffer);
		return 0;
	}

	int setDescription(wchar_t * buffer)
	{
		wcscpy_s(Description, wcslen(buffer)+1, buffer);
		return 0;
	}

	//get values
	long double getAmount()
	{
		return Amount;
	}

	wchar_t *getCategory()
	{
		return Category;
	}

	wchar_t *getDescription()
	{
		return Description;
	}


};

