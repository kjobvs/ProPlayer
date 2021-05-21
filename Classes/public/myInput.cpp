#include "myInput.h"
#include "myType.h"
#include <iostream>
using namespace std;

myInput::myInput()
{
}

myInput::~myInput()
{
}

int myInput::pleaseInput()
{
	string str;
	while (cin >> str)
	{
		if (myType::isNum(str))
		{
			return myType::turnNum(str);
		}
		else
		{
			cout << "Please input a Number." << endl;
		}
	}
	return -1;
}



int myInput::pleaseInput(int min, int max)
{
	int result = 1;
	bool condition = true;
	while (condition)
	{
		result = pleaseInput();
		if (result >= min && result <= max)
		{
			return result;
		}
		else
		{
			cout << "Please Input a number that is smaller than " << max << "and greater than" << min << endl;
		}
	}
}

bool myInput::pleaseInputBool()
{
	string str;
	bool condition = true;
	while (condition)
	{
		cin >> str;
		if (str.size() == 1 && (str[0] == 'y' || str[0] == 'Y'))
		{
			return true;
		}
		else if (str.size() == 1 && (str[0] == 'n' || str[0] == 'N'))
		{
			return false;
		}
		else
		{
			cout << " ÇëÊäÈë y/n." << endl;
		}
	}
	return NULL;
}