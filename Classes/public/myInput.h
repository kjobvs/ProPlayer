#pragma once
#include <string>

class myInput
{
private:
	myInput();
	~myInput();
public:
	static int pleaseInput();
	static int pleaseInput(int min, int max);
	static bool pleaseInputBool();
};

