#include "myScene.h"
#include <iostream>
#include <windows.h>
using namespace std;

void myScene::gotoXY(short x, short y)
{
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(std,pos);
}

void myScene::highLight(short x, short y, string str)
{
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std, FOREGROUND_RED |FOREGROUND_INTENSITY| BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	gotoXY(x, y);
	cout << str;
	SetConsoleTextAttribute(std, FOREGROUND_BLUE | FOREGROUND_GREEN |FOREGROUND_RED);
}

void myScene::dimLight(short x, short y, string str)
{
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std, FOREGROUND_RED | FOREGROUND_BLUE|FOREGROUND_GREEN | BACKGROUND_INTENSITY);
	gotoXY(x, y);
	cout << str;
	SetConsoleTextAttribute(std, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void myScene::setColor(char color)
{
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (color)
	{
	case 'r':
		SetConsoleTextAttribute(std, FOREGROUND_RED);
		break;
	case 'b':
		SetConsoleTextAttribute(std, FOREGROUND_BLUE);
		break;
	case 'g':
		SetConsoleTextAttribute(std, FOREGROUND_GREEN);
		break;
	case 'w':
		SetConsoleTextAttribute(std, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
		break;
	}
}

void myScene::hideCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = sizeof(cci);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hout, &cci);
}

void myScene::showCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = sizeof(cci);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hout, &cci);
}