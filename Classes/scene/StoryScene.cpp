#include "StoryScene.h"
#include "../DataLoader/DataManagerEx.h"
#include "../GuideMenuBar.h"
#include "../GameControl/GameControl.h"
#include "../public/CLFunction.h"

#include <vector>

#define STR myType::GBKToUTF8

using namespace std;
USING_NS_CC;

Scene* StoryScene::createScene()
{
	auto ptr = StoryScene::create();
	ptr->description = "StoryScene";
	return ptr;
}

Scene* StoryScene::createScene(string filename)
{
	auto ptr = StoryScene::create(filename);
	return ptr;
}

void StoryScene::addChild(Node* child, int ZOrder, int tag)
{
	if (child->getName() == "line")
	{
		lines.insert(make_pair(tag, DataManagerEx::getInstance()->getLineByTag(tag)));
		runLine();
		return;
	}
	Scene::addChild(child, ZOrder, tag);
}

void StoryScene::removeChildByName(const string &name, bool cleanup)
{
	if (name == "Dialog")
	{
		if (Dialog->isOpen())
		{
			Dialog->close();
		}
		if (!Dialog->isClosed())
		{
			return;
		}
	}
	Scene::removeChildByName(name, cleanup);
}

bool StoryScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	initDisplay();
	showScreen();
	initAnimation();
	this->scheduleUpdate();
	return true;
}

void StoryScene::initDisplay()
{
	initBackGround();
	initCGLayer();
	initGuideMenu();
	initDialog();
}

void StoryScene::initBackGround()
{
	Background = BackGroundLayer::create(backgroundFile);
	Background->setName("backGround");
	this->addChild(Background,0,0);
	Background->setPosition(Vec2(origin.x, origin.y));
}

void StoryScene::initCGLayer()
{
	auto CGLayer = Layer::create();
	CGLayer->setName("CGLayer");
	CGLayer->setPosition(Vec2(origin.x, origin.y));
	Scene::addChild(CGLayer, 500, 2);
}

void StoryScene::initDialog()
{
	Dialog = WindowLayer::create();
	Dialog->setContentSize(Size(visibleSize.width*0.85, visibleSize.height*0.25));
	Dialog->setName("Dialog");
	Scene::addChild(Dialog, 800, 400);
	if (Dialog != nullptr)
	{
		Dialog->setPosition(Vec2(origin.x+visibleSize.width / 2-Dialog->getBoundingBox().size.width/2, origin.y+10));
	}
}

void StoryScene::initGuideMenu()
{
	auto GuideMenu = GuideMenuBar::create();
	GuideMenu->setName("GuideMenu");
	GuideMenu->setPosition(origin.x, origin.y);
	Scene::addChild(GuideMenu,1200, 300);
	
}

void StoryScene::initAnimation()
{
	auto node = this->getChildByName("GuideMenu")->getChildByName("backBar");
	auto delay = DelayTime::create(1.5f);
	delay->setTag(AnimationSequenceStart.size());
	auto moveIn = MoveTo::create(0.6f, Vec2(0, visibleSize.height*0.9));
	auto easeIn = EaseIn::create(moveIn, 2.0f);
	auto moveBack = MoveTo::create(0.3f, Vec2(0,visibleSize.height*0.96));
	auto easeOut = EaseOut::create(moveBack, 2.0f);
	auto move = Sequence::create(easeIn, easeOut,nullptr);
	move->setTag(AnimationSequenceStart.size());
	AnimationSequenceStart.push_back(make_pair(this, delay));
	AnimationSequenceStart.push_back(make_pair(node, move));

	AnimationSequenceRun.push_back(make_pair(nullptr, nullptr));
	BaseScene::initAnimation();
}


void StoryScene::startScene()
{
	GameControl::getInstance()->advanceProgress();
}

void StoryScene::endScene()
{
}

void StoryScene::update(float delta)
{
	BaseScene::update(delta);
	updateActor();
}

void StoryScene::updateActor()
{
	for (auto it = actorsInScene.begin(); it !=  actorsInScene.end(); it++)
	{
		if (it->second->isVisible())
		{
			if (this->getChildByTag(it->second->getTag()) == nullptr && it->second->getSprite()!= nullptr)
				BaseScene::addChild(it->second->getSprite(),100, it->second->getTag());
			else
				it->second->changeMood();
		}
		else
		{
			if (this->getChildByTag(it->second->getTag()) != nullptr)
			{
				this->removeChildByTag(it->second->getTag());
				it->second->clearFace();
			}
		}
	}
}

StoryScene* StoryScene::create(string filename)
{
	StoryScene *pRet = new(std::nothrow) StoryScene();
	pRet->backgroundFile = filename;
	pRet->setDescription("StoryScene");
	pRet->actorTag = ACTORTAG;
	pRet->nodeTag = TAGSTARTVALUE;
	if (pRet && pRet->init())
	{
			pRet->autorelease();
			return pRet;
	}
    else
    {
        delete pRet; 
        pRet = nullptr;
        return nullptr;
    }
}

void StoryScene::runLine()
{
	Line* line = (--lines.end())->second;
	Actor* actor= line->getActor();
	if (this->getChildByName("Dialog") == nullptr)
		initDialog();
	if (actor != nullptr)
	{
		log("error message");
		actor->setVisible(true);
		actorsInScene.insert(make_pair(actor->getTag(),actor));
		Dialog->enableActorName(true,line->getActorName());
	}
	else
	{
		Dialog->enableActorName(false);
	}
	Dialog->addNewString(line->getWord());
}

void StoryScene::onExit()
{
	for (auto it = actorsInScene.begin(); it != actorsInScene.end(); it++)
	{
		it->second->clearFace();
	}
	BaseScene::onExit();
}