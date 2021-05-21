#include "FileAccess.h"
#include "myType.h"
#include <iostream>
#include <time.h>
using namespace std;

FileIO::FileIO(fstream *fs,string _path)
{
	fIO = fs;
	path = _path;
}

void FileIO::write(string str, bool mode)
{
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	endLine(mode);
	fIO->close();
}

void FileIO::write(string str, char end)
{

		fIO->open(path, ios::out | ios::app);
		for (auto it = str.begin(); it != str.end(); it++)
		{
			char temp = *it;
			fIO->write((char*)&temp, sizeof(temp));
		}
		if (end == ' ')
		{
		}
		else
		{
			endLine(end);
		}
		fIO->close();
}

void FileIO::write(string str, int num, bool mode)
{
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	str = myType::turnString(num);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	endLine(mode);
	fIO->close();
}

void FileIO::write(tm* _time, string str, bool mode)
{
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	fIO->close();
	write(_time->tm_mon,false);
	write(_time->tm_year, false);
	write(_time->tm_mday, false);
	write(_time->tm_wday, false);
	write(_time->tm_yday, false);
	write(_time->tm_hour, false);
	write(_time->tm_min, false);
	write(_time->tm_sec, false);
	write(_time->tm_isdst, true);
}

void FileIO::write(int num, bool mode)
{
	string str = myType::turnString(num);
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	endLine(mode);
	fIO->close();
}

void FileIO::write(vector<string> str, bool mode)
{
	fIO->open(path, ios::out | ios::app);
	for (size_t i = 0; i < str.size(); i++)
	{
		for (auto it = str[i].begin(); it != str[i].end(); it++)
		{
			char temp = *it;
			fIO->write((char*)&temp, sizeof(temp));
		}
	}
	endLine(mode);
	fIO->close();
}

void FileIO::write(COORD pos, bool mode)
{
	string str = "{";
	str.append(myType::turnString(pos.X));
	str.push_back(',');
	str.append(myType::turnString(pos.Y));
	str.push_back('}');
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&str, sizeof(str));
	}
	endLine(mode);
	fIO->close();
}

void FileIO::write(string str, COORD pos, bool mode)
{
	fIO->open(path, ios::out | ios::app);
	for (auto it = str.begin(); it != str.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	string myCoord = "{";
	myCoord.append(myType::turnString(pos.X));
	myCoord.push_back(',');
	myCoord.append(myType::turnString(pos.Y));
	myCoord.push_back('}');
	for (auto it = myCoord.begin(); it != myCoord.end(); it++)
	{
		char temp = *it;
		fIO->write((char*)&temp, sizeof(temp));
	}
	endLine(mode);
	fIO->close();
}

void FileIO::endLine(bool mode)
{
	if (mode)
	{
		fIO->write((char*)&newLine, sizeof(newLine));
	}
	else
	{
		fIO->write((char*)&semiC, sizeof(comma));
	}

}

void FileIO::endLine(char end)
{
	auto symbol = end;
	fIO->write((char*)&end, sizeof(end));
}

vector<string> FileIO::read()
{
	vector<string> result;
	string tempS = "";
	fIO->open(path, ios::in);
	while (!(fIO->eof()))
	{
		char temp;
		fIO->get(temp);
		if (temp == '\n')
		{
			result.push_back(tempS);
			tempS.clear();
		}
		else
		{
			tempS.push_back(temp);
		}
	}
	result.push_back(tempS);
	fIO->close();
	return result;
}

