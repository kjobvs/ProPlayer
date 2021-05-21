#pragma once
#include <vector>
#include "cocos2d.h"
class MultiNode
{
public:
	void pushTarget(cocos2d::Node* target,GLubyte startColor,GLubyte endColor);
protected:
	std::vector<cocos2d::Node*> targets;
	std::vector<GLubyte> fromOpacity;
	std::vector<GLubyte> toOpacity;
};

