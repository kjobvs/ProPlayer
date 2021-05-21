#pragma once
#include <string>

class myScene
{
	myScene() = default;
public:
	static void gotoXY(short x, short y);
	static void highLight(short x, short y,std::string str);
	static void dimLight(short x, short y, std::string str);
	static void hideCursor();
	static void showCursor();
	static void setColor(char color);
};

