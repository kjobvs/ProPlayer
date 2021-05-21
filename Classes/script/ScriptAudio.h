#pragma once
#include "Script.h"

class ScriptAudio:
	public Script
{
public:
	void setContents(std::map<std::string, std::string> contents) override;
	int start() override;
	int getAuidoID();
private:
	std::string filePath;
	int id;
};

