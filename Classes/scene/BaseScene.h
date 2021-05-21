#pragma once
#include "cocos2d.h"
#include <list>
#include <string>
#include <map>

#define TAGSTARTVALUE 100
#define SCENEBOOT 0
#define SCENERUNNING 1
#define SCENEEND 2

class BaseScene:
	public cocos2d::Scene
{
public:
	BaseScene();
	virtual bool init();
	cocos2d::Scene* recallScene(unsigned int pos = 0);
	void setDescription(std::string des);
	std::string getDescription();
	cocos2d::Action* getCurrentAnimation();
protected:
	cocos2d::Sprite* createSprite(std::string imgPath, int tag, std::string name, cocos2d::Vec2 position = { 0,0 }, cocos2d::Vec2 anchor = {0,0});
	void addNode(cocos2d::Node* node);

	virtual void update(float delta); //需在子类实现中反复调用；
	virtual void updateAnimation();
	virtual void updateSceneStatus();

	virtual void startScene() = 0;
	virtual void endScene() = 0;

	void problemLoading(std::string filename,BaseScene* name);

	void closeApp();
	void replaceScene(cocos2d::Scene* replace);
	void pushScene(cocos2d::Scene* push);
	void popScene();

	void updateSceneStack();

	virtual void initDisplay()=0;
	virtual void showScreen();
	virtual void initAnimation();

	static std::string description;
	static std::string backgroundFile;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;


	static std::list<cocos2d::Scene*> sceneStack;
	static std::list<cocos2d::Event*> eventStack; //暂定，不一定需要；


	std::map<int,cocos2d::Node*> nodeStack;
	std::list<std::pair<cocos2d::Node*, cocos2d::Action*>> AnimationSequenceStart;
	std::list<std::pair<cocos2d::Node*, cocos2d::Action*>> AnimationSequenceRun;
	std::list<std::pair<cocos2d::Node*, cocos2d::Action*>> AnimationSequenceEnd;
	std::list<std::pair<cocos2d::Node*, cocos2d::Action*>> AnimationSequenceCustom;
	int sceneStatus;
	bool animStatus;
	int nodeTag;
};

