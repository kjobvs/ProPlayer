#pragma once
#include <string>
#include <time.h>
#include <windows.h>
class myType
{
public:
	static bool isNum(std::string str);
	static int turnNum(std::string str);
	static int turnNum(std::string str, int digit);
	static int turnNum(char str);
	static void turnTime(tm *saveTime, std::string str);
	static COORD turnCOORD(std::string str);
	static std::string turnString(int num);
	static std::string turnString(char* head, size_t size);
	static void padZero(int digit,std::string &str);
	static std::string padZero(int digit, int num);
	static std::string replaceSubStr(std::string strMain, std::string toReplace);

	static std::string GBKToUTF8(std::string gbkStr, const char* fromCode = "gb2312", const char* toCode= "utf-8");
};
