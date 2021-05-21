#pragma once
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <string>

class FileIO
{
public:
	FileIO(std::fstream *fs, std::string _path);
	void write(std::string str,bool mode = true);
	void write(std::string str, char end);
	void write(int num, bool mode = true);
	void write(COORD pos, bool mode = true);
	void write(std::string str, int num, bool mode=true);
	void write(std::string str, COORD pos, bool mode = true);
	void write(tm* _time, std::string str = "", bool mode = true);
	void write(std::vector<std::string> str, bool mode = true);
	std::vector<std::string> read();
private:
	void endLine(bool mode);
	void endLine(char end);
	char newLine = '\n';
	char comma = ',';
	char lSemi = '[';
	char rSemi = ']';
	char lPoint = '{';
	char rPoint = '}';
	char semiC = ';';
	std::string path = "";
	std::fstream *fIO = nullptr;
};

