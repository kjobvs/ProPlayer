#pragma once
#include "Script.h"
class ScriptSprite:
	public Script
{
public:
	void setContents(std::map<std::string, std::string> contents) override;
	int start() override;
private:
	cocos2d::Sprite* sprite;
	std::string pathFile;   

	int closeDialog();

	int addCG();
	int removeCG();
	int addItem();
	int removeItem();
};

