#pragma once
#include <list>
#include "BaseScene.h"

class BootScene:
	public BaseScene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(BootScene);

	void skipAnimation();
private:
	void initInput();
	void initDisplay() override;
	void initAnimation() override;
	void initStartAnimation();
	void initRunAnimation();
	void initEndAnimation();

	void update(float delta) override;

	void startScene()override;
	void endScene() override;

	bool isFileLoaded();

	std::list<cocos2d::Label*> labelList;
};

