#include "myType.h"
#include "myData.h"
#include <string>
#include <iostream>
using namespace std;

myData::myData()
{
}


myData::~myData()
{
}

int myData::getNumber(string str)
{
	string result;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ':')
		{
			for (size_t j = i+1; j < str.size(); j++)
			{
				result.push_back(str[j]);
			}
			break;
		}
	}
	return myType::turnNum(result);
}

list<int> myData::getListNum(string str, char seperator)
{
	list<int> result;
	while (str.find('|') != string::npos)
	{
		result.push_back(myType::turnNum(str.substr(0, str.find('|'))));
		str.erase(0, str.find('|') + 1);
	}
	if (str.size() > 0)
		result.push_back(myType::turnNum(str));
	else
		result.push_back(-1);

	return result;
}

COORD myData::getCOORD(string str)
{
	COORD result;
	if (str.find('{') != -1 && str.find('}') != -1)
	{
		for (size_t i = 0; i<str.size(); i++)
		{
			if (str[i] == '{')
			{
				string temp;
				size_t j = i + 1;
				for (; str[j] != ','; ++j)
				{
					temp.push_back(str[j]);
				}
				result.X = myType::turnNum(temp);
				++j;
				temp.clear();
				for (; str[j] != '}'; ++j)
				{
					temp.push_back(str[j]);
				}
				result.Y = myType::turnNum(temp);
				return result;
			}
		}
	}
	else
	{
		cout << "failure! there is no COORD included in the string." << endl;
		system("pause");
		return{ -1, -1 };
	}
}

