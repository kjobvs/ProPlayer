#pragma once
#include "cocos2d.h"
#include <string>
#include <map>

class Script:
	public cocos2d::Ref
{
public:
	void setTag(int _tag);
	int getTag();
	void setType(int _type);
	int getType();
	void setDescription(std::string _des);
	std::string getDescription();
	virtual void setContents(std::map<std::string,std::string> contents) = 0;
	virtual int start()=0;
protected:
	int tag;
	int type;
	std::string description;
};

