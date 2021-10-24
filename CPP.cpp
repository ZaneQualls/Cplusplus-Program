#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <format>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	//return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void DisplayHisto() 
{
	ifstream infile("frequency.dat");
	string a; 
	int b;

	while (infile >> a >> b)
	{
		cout << a << " " << string(b, '*') << endl;
	}
}

void DisplayMenu()
{
	cout << string(47, '-') << endl;
	cout << "1: List all items puchased" << endl;
	cout << "2: How many times a specific item was purchased" << endl;
	cout << "3: Histogram listing all items purchased" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
	cout << string(47, '-') << endl;
}

bool running = true;
string newValue = "";

void GetInput() 
{
	while (running)
	{
		string userInput;
		cin >> userInput;
		
		if (userInput == "1")
		{
			system("CLS");
			cout << "Display list of all items: \n\n";
			CallProcedure("ListAll");
		}
		else if (userInput == "2")
		{
			char buffer[100];
			system("CLS");
			cout << "Enter specific item to check: ";
			cin >> newValue;
			callIntFunc("GetOneItem", newValue);
		}
		else if (userInput == "3")
		{
			system("CLS");
			cout << "Display Histogram: \n\n";
			CallProcedure("CreateHisto");
			DisplayHisto();
		}
		else if (userInput == "4")
		{
			running = false;
		}
		else 
		{
			system("CLS");
			cout << string(29, '-') << endl;
			cout << "Incorrect Input. Try again..." << endl;
			cout << string(29, '-') << endl;
			DisplayMenu();
			GetInput();
		}
			
		running = false;
	}
}

void main()
{
	DisplayMenu();
	GetInput();
}

/*CallProcedure("printsomething");
cout << callIntFunc("PrintMe", "House") << endl;
cout << callIntFunc("SquareValue", 2);*/

// Loop through the list of items
// find any duplicates and increat the count of that item by 1
// print the item once plus he ammount of duplicates.

// Take in input of item to search. look for all the times it is pinted
// print the item and the amount

//Write a Python function that reads an input file(CS210_Project_Three_Input_File, 
//which is linked in the Supporting Materials section) and then creates a file,
//which contains the wordsand their frequencies.The file that you create should be named frequency.dat, 
//which needs to be specified in your C++ codeand in your Python code.Note that 
//you may wish to refer to work you completed in a previous assignment where you practiced
//reading and writing to a file. 
//Some of your code from that work may be useful to reuse or manipulate here
//.The frequency.dat file should include every item(represented by a word) 
//paired with the number of times that item appears in the input file.For example, 
//the file might read as follows :
//Potatoes 4
//Pumpkins 5
//Onions 3
//Write C++ code to read the frequency.dat file and display a histogram.
//Loop through the newly created file and read the name and frequency on each row.
//Then print the name, followed by asterisks or another special character to represent the numeric amount.
//The number of asterisks should equal the frequency read from the file.For example, 
//if the file includes 4 potatoes, 5 pumpkins, and 3 onions then your text -
//based histogram may appear as represented below.However, you can alter the appearance or color of the histogram 
//in any way you choose.
//Potatoes * ***
//Pumpkins * ****
//Onions * **