#pragma once
#include "Script.h"
#include "../DataLoader/Line.h"

class ScriptLine:
	public Script
{
public:
	void setContents(std::map<std::string, std::string> contents) override;
	Line* getLine();
	int start() override;
private:
	Line* line;

};

