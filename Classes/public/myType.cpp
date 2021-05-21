#include "myType.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "cocos2d/external/win32-specific/icon/include/iconv.h"
using namespace std;

bool myType::isNum(string str)
{
	if (str[0] == '-' || str[1] == '+')
	{
		str.erase(str.begin());
	}
	if (str.size() > 0)
	{
		for (const auto i : str)
		{
			if (i < '0' || i>'9')
				return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

int myType::turnNum(char str)
{
	switch (str)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	default:
		return -1;
		break;
	}
}

int myType::turnNum(string str)
{
	int sign = 1;
	int result = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign *= -1;
		str.erase(str.begin());
	}
	stringstream ss;
	ss << str;
	ss >> result;
	result *= sign;
	return result;
}

int myType::turnNum(string str, int digit)
{
	string result;
	for (size_t i = 0; i < digit; i++)
	{
		if (str[i] != 0)
		{
			for (size_t j = i; j < digit; j++)
			{
				result.push_back(str[j]);
			}
			return turnNum(result);
		}
	}
	return 0;
}

void myType::turnTime(tm* saveTime, string str)
{
	string result;
	vector<int> time;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ',')
		{
			result.push_back(str[i]);
		}
		else
		{

			time.push_back(turnNum(result));
			result.clear();
		}
	}
	time.push_back(turnNum(result));
	saveTime->tm_mon = time[0];
	saveTime->tm_year = time[1];
	saveTime->tm_mday = time[2];
	saveTime->tm_wday = time[3];
	saveTime->tm_yday = time[4];
	saveTime->tm_hour = time[5];
	saveTime->tm_min = time[6];
	saveTime->tm_sec = time[7];
	saveTime->tm_isdst = time[8];
}

string myType::turnString(char* head, size_t size)
{
	string result = " ";
	for (size_t i = 0; head[i]!= head[size]; i++)
	{
		result.push_back(head[i]);
	}
	return result;
}

COORD myType::turnCOORD(string str)
{
	size_t i = 0;
	string temp;
	COORD result;
	for (; i < str.size() && str[i] != '{'; ++i)
		continue;
	for (++i; i < str.size() && str[i] != ','; ++i)
		temp.push_back(str[i]);
	result.X = turnNum(temp);
	temp.clear();
	for (++i; i < str.size() && str[i] != '}'; ++i)
		temp.push_back(str[i]);
	result.Y = turnNum(temp);
	return result;
}

string myType::turnString(int num)
{
	string result;
	stringstream ss;
	ss << num;
	ss >> result;
	return result;
}

void myType::padZero(int digit,string &str)
{
	if (str.size() < digit)
	{
		while(str.size() < digit)
		{
			str = '0' + str;
		}
	}
}

string myType::padZero(int digit, int num)
{
	string str = turnString(num);
	padZero(digit, str);
	return str;
}

string myType::replaceSubStr(string strMain, string toReplace)
{
	string result = strMain;
	for (auto it = result.begin(); it != result.end(); it++)
	{
		if (*it == '%')
		{
			result.replace(--it, ++it,toReplace);
			break;
		}
	}
	return result;
}

string myType::GBKToUTF8(std::string gbkStr, const char* fromCode, const char* toCode)
{
		iconv_t iconvH;
		iconvH = iconv_open(toCode, fromCode);
		if (iconvH == 0)
			return gbkStr;
		const char* strChar = gbkStr.c_str();
		const char** pin = &strChar;
		size_t strLength = gbkStr.length();
		char *outbuf = (char*)malloc(strLength * 4);
		char *pBuff = outbuf;
		memset(outbuf, 0, strLength * 4);
		size_t outLength = strLength * 4;
		if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
		{
		iconv_close(iconvH);
		return gbkStr;
		}
		gbkStr = pBuff;
		iconv_close(iconvH);
		return gbkStr;
}