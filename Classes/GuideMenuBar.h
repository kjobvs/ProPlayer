#pragma once
#include "TouchLayer.h"

class GuideMenuBar:
	public TouchLayer
{
public:
	std::string getDescription() const override;
	bool init() override;
	void initInput();

	CREATE_FUNC(GuideMenuBar);
	CC_CONSTRUCTOR_ACCESS:
	GuideMenuBar();
	~GuideMenuBar();
private:
	void initButtons();
	void initFastSave();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

