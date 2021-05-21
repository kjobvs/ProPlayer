#include "BootScene.h"
#include "StartScene.h"
#include "../customAction/MultiNodeFade.h"
#include "../public/CLFunction.h"
#include "../DataLoader/DataManagerEx.h"
#include "../GameControl/GameControl.h"
#include "../script/ScriptManager.h"

#include <string>
using namespace std;
USING_NS_CC;

Scene* BootScene::createScene()
{
   auto ptr =  BootScene::create();
   ptr->description = "BootScene";
   return ptr;
}

bool BootScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	BaseScene::nodeTag = TAGSTARTVALUE;

	initDisplay();
	showScreen();
	initAnimation();
	initInput();
	this->scheduleUpdate();
	return true;
}

void BootScene::initInput()
{
	auto inputEvent = EventListenerMouse::create();
	inputEvent->onMouseDown = CC_CALLBACK_0(BootScene::skipAnimation,this);
	_eventDispatcher->addEventListenerWithFixedPriority(inputEvent,5);
}

void BootScene::initDisplay()
{
	auto symbol = Sprite::createWithSpriteFrameName("logo.png");
	auto label = Label::createWithTTF("Loading", "fonts/CaoTTF.ttf", 16);
	symbol->setScale(visibleSize.width*0.18/(symbol->getContentSize().width));
	symbol->setPosition(visibleSize.width / 2, visibleSize.height / 2+label->getBoundingBox().size.height*1.5/2);
	symbol->setName("symbol");
	symbol->setOpacity(0);
	label->setAnchorPoint(Vec2(0.5,0.5));
	label->setPosition(Vec2(visibleSize.width/2, symbol->getBoundingBox().getMinY() - label->getBoundingBox().size.height*1.5));
	label->setName("label");
	label->setOpacity(0);
	labelList.push_back(label);
	auto contentsLayer = Layer::create();
	contentsLayer->addChild(symbol);
	contentsLayer->addChild(label);
	contentsLayer->setPosition(origin.x, origin.y-label->getBoundingBox().size.height*1.5/2);
	contentsLayer->setName("contentsLayer");
	addNode(contentsLayer);
}

void BootScene::initAnimation()
{
	auto _schedule = Director::getInstance()->getScheduler();
	_schedule->schedule([this](float time) {
		if (labelList.size() > 0)
		{
			auto label = *(labelList.begin());
			string str = label->getString();
			if (str.size() - 7 < 3)
			{
				str.push_back('.');
				label->setString(str);
			}
			else
			{
				label->setString("LOADING");
			}
		}
		},this,1.0f, !this->isRunning(),"updateLabel");
	initStartAnimation();
	initRunAnimation();
	initEndAnimation();
	BaseScene::initAnimation();
}

void BootScene::initStartAnimation()
{
	auto fadeIn = FadeIn::create(4.0);
	auto fadeOut = FadeOut::create(4.0);
	auto startAnimation = Sequence::create(fadeIn->clone(), nullptr);
	startAnimation->setTag(AnimationSequenceStart.size());
	AnimationSequenceStart.push_back(make_pair(this->getChildByName("contentsLayer")->getChildByName("symbol"), startAnimation));
}

void BootScene::initRunAnimation()
{
	int targetX = this->getChildByName("contentsLayer")->getBoundingBox().getMinX();
	int targetY = this->getChildByName("contentsLayer")->getChildByName("label")->getBoundingBox().size.height*1.5 / 2;
	auto moveTo = MoveTo::create(0.3, Vec2(targetX, targetY));
	moveTo->setTag(AnimationSequenceRun.size());
	AnimationSequenceRun.push_back(make_pair(this->getChildByName("contentsLayer"), moveTo));
	
	Action* fadeIn = FadeIn::create(1.0);
	fadeIn->setTag(AnimationSequenceRun.size());
	AnimationSequenceRun.push_back(make_pair(this->getChildByName("contentsLayer")->getChildByName("label"), fadeIn));

	auto blinkIn = MultiNodeFadeIn::create(1.0);
	auto blinkOut = MultiNodeFadeOut::create(1.0);
	blinkIn->pushTarget(this->getChildByName("contentsLayer")->getChildByName("symbol"), (GLubyte)0, (GLubyte)255);
	blinkOut->pushTarget(this->getChildByName("contentsLayer")->getChildByName("symbol"), (GLubyte)255, (GLubyte)0);
	auto instantBlink = Sequence::create(blinkOut, blinkIn, nullptr);
	auto runningAnimation = RepeatForever::create(instantBlink);
	runningAnimation->setTag(AnimationSequenceRun.size());
	AnimationSequenceRun.push_back(make_pair(this->getChildByName("contentsLayer"), runningAnimation));

	auto fadeOut = FadeOut::create(1.0);
	fadeOut->setTag(AnimationSequenceRun.size());
	AnimationSequenceRun.push_back(make_pair(this->getChildByName("contentsLayer")->getChildByName("label"),fadeOut));

	auto label = this->getChildByName("contentsLayer")->getChildByName("label");
	auto moveBack = MoveTo::create(0.3, Vec2(origin.x,origin.y-targetY));
	moveBack->setTag(AnimationSequenceRun.size());
	AnimationSequenceRun.push_back(make_pair(this->getChildByName("contentsLayer"), moveBack));
}

void BootScene::initEndAnimation()
{
	auto temp = FadeOut::create(4.0f);
	temp->setTag(AnimationSequenceRun.size());
	AnimationSequenceEnd.push_back(make_pair(this->getChildByName("contentsLayer")->getChildByName("symbol"), temp));
}

void BootScene::update(float delta)
{
	BaseScene::update(delta);
	if (sceneStatus == SCENERUNNING)
	{
		if (isFileLoaded()&& getCurrentAnimation()->getTag() == 2)
		{
			auto animation = *AnimationSequenceRun.begin();
			auto action = animation.first->getActionByTag(animation.second->getTag());
			if (action != nullptr)
			{
				action->stop();
				action->release();
			}
			animStatus = false;
			AnimationSequenceRun.erase(AnimationSequenceRun.begin());
		}
	}
}

void BootScene::startScene()
{
	DataManagerEx::getInstance()->loadFile();
	ScriptManager::getInstance()->loadScript();
	GameControl::getInstance()->loadConfig();
}

void BootScene::endScene()
{
	this->getChildByName("contentsLayer")->getChildByName("symbol")->setVisible(false);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StartScene::createScene(), Color3B::BLACK));
}

bool BootScene::isFileLoaded()
{
	return DataManagerEx::getInstance()->isLoaded();
}

void BootScene::skipAnimation()
{
	auto action = getCurrentAnimation();
	if (action != nullptr && action->getTag() != 2 && sceneStatus != SCENERUNNING)
	{
		Director::getInstance()->getScheduler()->setTimeScale(8.0f);
	}
}