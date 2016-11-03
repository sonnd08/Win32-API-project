Student id: 1412465

Name: Nguyễn Đình Sơn

Email: 001.IceTea@gmail.com

What i have done:
	- Create a program to manage your expenses

	  
Main flow (main success scenario when using the app)
	Example 1:
	- Open program
	- Enter "30000" to "Amount" box
	- Select "Ăn uống" from "Category"
	- Fill description with "test"
	- Click "Add" button
	- "Expenses list" will show "30000		Ăn uống		test"
	- "Total Expense: " change from "0" to "30.000"
	- Bar char show that "Ăn uống" = "30000(100%)", others category = "0(0%")
	
	Example 2:	
	- Open program
	- Enter "30000" to "Amount" box
	- Select "Ăn uống" from "Category"
	- Fill description with "test"
	- Click "Add" button
	- Now, close program
	- Reopen program
	- Program load previous data from file
	- "Expenses list" will show "30000		Ăn uống		test"
	- "Total Expense: " change from "0" to "30.000"
	- Bar char show that "Ăn uống" = "30000(100%)", others category = "0(0%")
	
	Example 3:
	- Open program
	- Click "Clear data" button 
	- "Expense list" now empty
	- "Total expense: " = "0"
	- Bar chart show that every category = "0(0%)"
	
Additional flow
	Example 1:
	- Open program
	- Try to enter "-sadxc" to "Amount" box 
	- A popup show up warn you that "You can only type a number here"
	
	
	- Example 2:
	- Open program
	- Leave "Amount" and "Category" blank
	- A message box show up warn you that 
		"- Amount of money must be greater than zero! 
		 - Category must not be empty", L"Input error!"
	
Screen recording:
https://www.youtube.com/watch?v=S1tEj8u_-7Y
		
IDE: Visual Studio 2015