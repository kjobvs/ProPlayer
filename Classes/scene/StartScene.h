#pragma once
#include "BaseScene.h"
#include "../DataLoader/Actor.h"

class StartScene:
	public BaseScene
{
public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(std::string filename);
	bool init() override;
	CREATE_FUNC(StartScene);
protected:
	void initDisplay() override;
	void initActor();
	void initMenu();
	void initAnimation() override;
	void initStartAnimation();
	void initRunAnimation();
	void showScreen() override;

	void update(float delta) override;

	void onExit() override;

	void startScene() override;
	void endScene() override;
	void loadScene();
	void setScene();

	bool checkLoadFile();
protected:
	std::map<int, Actor*> actorsInScene;

};

