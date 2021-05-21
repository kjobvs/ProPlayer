#pragma once
#include <string>
#include <list>
#include <vector>
#include <windows.h>
class myData
{
public:
	static int getNumber(std::string str);
	static std::list<int> getListNum(std::string str,char seperator = '|');
	static COORD getCOORD(std::string str);
private:
	myData();
	~myData();
};

