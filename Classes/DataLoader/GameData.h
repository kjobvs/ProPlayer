#pragma once
#include <string>
#include <list>
#include <map>
#include "cocos2d.h"

class GameData:
	public cocos2d::Node
{
public:
	virtual void setTag(int _tag);
	virtual int getTag();
	virtual void setDescription(std::string des);
	virtual std::string getDescription();
	virtual ~GameData() = default;
protected:
	int tag;
	std::string description;
};

