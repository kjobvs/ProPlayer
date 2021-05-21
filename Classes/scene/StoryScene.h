#pragma once
#include "BaseScene.h"
#include "../DataLoader/Line.h"
#include "../WindowLayer.h"
#include "../BackGroundLayer.h"

class StoryScene:
	public BaseScene
{
#define ACTORTAG 200
public:
	static Scene* createScene();
	static Scene* createScene(std::string filename);
	bool init() override;
	CREATE_FUNC(StoryScene);
	static StoryScene* create(std::string filename);
	void removeChildByName(const std::string &name, bool cleanup = true) override;
	void addChild(Node* child, int ZOrder, int tag) override;
protected:
	std::map<int, Line*> lines;
	std::map<int, Actor*> actorsInScene;

	int actorTag;

	void onExit() override;
private:
	void initDisplay() override;
	void initBackGround();
	void initCGLayer();
	void initGuideMenu();
	void initDialog();
	void initAnimation() override;
	
	void initInput();

	void update(float delta) override;
	void updateActor();

	void startScene() override;
	void endScene() override;
     
	void runLine();

	WindowLayer* Dialog;
	BackGroundLayer* Background;

};

