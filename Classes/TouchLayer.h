#pragma once
#include "cocos2d.h"
class TouchLayer:
	public cocos2d::Layer
{
public:
	static TouchLayer* create();
	std::string getDescription() const override;
	bool init() override;

CC_CONSTRUCTOR_ACCESS:
	TouchLayer();
	virtual ~TouchLayer();
};

