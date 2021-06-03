#include "StartScene.h"
#include "../GameControl/GameControl.h"
#include "../DataLoader/DataManagerEx.h"
#include "../public/CLFunction.h"
#include "StoryScene.h"
using namespace std;
USING_NS_CC;

#define STR myType::GBKToUTF8


Scene* StartScene::createScene()
{
	auto ptr = StartScene::create();
	ptr->description = "StartScene";
	return ptr;
}

Scene* StartScene::createScene(string filename)
{
	auto ptr = StartScene::create();
	ptr->description = "StartScene";
	ptr->backgroundFile = filename;
	return ptr;
}

bool StartScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	BaseScene::nodeTag = TAGSTARTVALUE;

	initDisplay();
	showScreen();
	initAnimation();
	this->scheduleUpdate();
	return true;
}

void StartScene::initDisplay()
{
	createSprite("img/background/000.png", 0, "backGround", Vec2(origin.x, origin.y));
	initActor();
	initMenu();
}

void StartScene::initActor()
{
	int tag = GameControl::getInstance()->randomActor();
	auto actor = DataManagerEx::getInstance()->getActorByTag(tag);
	if (actor != nullptr)
	{
		actor->setVisible(true);
		actor->getSprite()->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
		actor->getSprite()->setOpacity(18);
		actor->getSprite()->setScale(1.8);
		actorsInScene[actor->getTag()] = actor;
	}
}

void StartScene::initMenu()
{
	auto buttonStart = MenuItemSprite::create(Sprite::createWithSpriteFrameName("button00.png"), Sprite::createWithSpriteFrameName("button00clicked.png"), Sprite::createWithSpriteFrameName("button00.png"), CC_CALLBACK_0(StartScene::endScene, this));
	auto buttonLoad = MenuItemSprite::create(Sprite::createWithSpriteFrameName("button00.png"), Sprite::createWithSpriteFrameName("button00clicked.png"), Sprite::createWithSpriteFrameName("button00.png"), CC_CALLBACK_0(StartScene::loadScene, this));
	auto buttonSet = MenuItemSprite::create(Sprite::createWithSpriteFrameName("button00.png"), Sprite::createWithSpriteFrameName("button00clicked.png"), Sprite::createWithSpriteFrameName("button00.png"), CC_CALLBACK_0(StartScene::setScene, this));
	auto buttonExit = MenuItemSprite::create(Sprite::createWithSpriteFrameName("button00.png"), Sprite::createWithSpriteFrameName("button00clicked.png"), Sprite::createWithSpriteFrameName("button00.png"), CC_CALLBACK_0(StartScene::closeApp, this));
	buttonLoad->getDisabledImage()->setColor(Color3B::GRAY);
	auto start = Label::createWithTTF(STR("开    始"), "fonts/CaoTTF.ttf", 16);
	auto load = Label::createWithTTF(STR("继    续"), "fonts/CaoTTF.ttf", 16);
	load->setName("load");
	auto set = Label::createWithTTF(STR("设    置"), "fonts/CaoTTF.ttf", 16);
	auto end = Label::createWithTTF(STR("退    出"), "fonts/CaoTTF.ttf", 16);
	buttonStart->addChild(start);
	buttonLoad->addChild(load);
	buttonSet->addChild(set);
	buttonExit->addChild(end);
	start->setPosition(start->getParent()->getBoundingBox().size / 2);
	load->setPosition(load->getParent()->getBoundingBox().size / 2);
	set->setPosition(set->getParent()->getBoundingBox().size / 2);
	end->setPosition(end->getParent()->getBoundingBox().size / 2);
	auto menu = Menu::create(buttonStart, buttonLoad, buttonSet, buttonExit, nullptr);
	menu->alignItemsVerticallyWithPadding(2.5f);
	menu->setPosition(Vec2(visibleSize.width - buttonExit->getBoundingBox().size.width*1.1, buttonExit->getBoundingBox().size.height*1.1*menu->getChildrenCount() / 2));
	menu->setScale(0.8);
	menu->setOpacity(0);
	menu->setName("menu");
	addNode(menu);
	if (!checkLoadFile())
	{
		buttonLoad->setEnabled(false);
		buttonLoad->getChildByName("load")->setColor(Color3B::GRAY);
	}
	else
	{
		buttonLoad->setEnabled(true);
	}
}

void StartScene::showScreen()
{
	BaseScene::showScreen();
	for (auto it = actorsInScene.begin(); it != actorsInScene.end(); it++)
	{
		if (it->second->isVisible())
		{
			this->addChild(it->second->getSprite(),it->first);
		}
	}
}

void StartScene::initAnimation()
{
	initStartAnimation();
	initRunAnimation();
	BaseScene::initAnimation();
}

void StartScene::initStartAnimation()
{
	auto target = actorsInScene.begin()->second;
	auto scale = ScaleTo::create(1.2f,0.9f);
	auto fade = FadeTo::create(2.0f, 255);
	auto move = MoveTo::create(1.5f, Vec2(origin.x,origin.y+visibleSize.height*0.85));
	auto spawn = Spawn::create(scale, fade, move, nullptr);
	auto ease = EaseIn::create(spawn,1.5f);
	spawn->setTag(target->getTag());
	AnimationSequenceStart.push_back(make_pair(target->getSprite(), spawn));
	auto fadeM = FadeIn::create(0.8f);
	auto easeM = EaseIn::create(fadeM, 0.8f);
	easeM->setTag(this->getChildByName("menu")->getTag());
	AnimationSequenceStart.push_back(make_pair(this->getChildByName("menu"), easeM));
}

void StartScene::initRunAnimation()
{
	AnimationSequenceRun.push_back(make_pair(nullptr, nullptr));
}

void StartScene::update(float delta)
{
	BaseScene::update(delta);
}

void StartScene::startScene()
{}

void StartScene::endScene()
{
	GameControl::getInstance()->startGame();
}

void StartScene::loadScene()
{}

void StartScene::setScene()
{}

bool StartScene::checkLoadFile()
{
	for (size_t i = 0; i < GameControl::getInstance()->getMaxSaveFile(); i++)
	{
		string pathName = "Save/saveFile" + myType::padZero(2,i) + ".sav";
		log(pathName.c_str());
		bool result = FileUtils::getInstance()->isFileExist(pathName);
		if (result)
			return true;
		else
			continue;
	}
	return false;
}

void StartScene::onExit()
{
	for (auto it = actorsInScene.begin(); it != actorsInScene.end(); it++)
	{
		it->second->clearFace();
	}
	BaseScene::onExit();
}