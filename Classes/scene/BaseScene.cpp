#include "BaseScene.h"
#include "../public/CLFunction.h"

using namespace std;
USING_NS_CC;

list<Scene*> BaseScene::sceneStack = {};
list<Event*> BaseScene::eventStack = {};
string BaseScene::description = "";
string BaseScene::backgroundFile = "";

bool BaseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	if (visibleSize.width > 0 && visibleSize.height > 0)
	{
		return true;
	}
	return false;
}

void BaseScene::showScreen()
{
	for (auto it = nodeStack.begin(); it != nodeStack.end(); it++)
	{
		this->addChild(it->second, it->first);
	}
}

std::string BaseScene::getDescription()
{
	return description;
}

void BaseScene::setDescription(string des)
{
	description = des;
}

Action* BaseScene::getCurrentAnimation()
{
	list<pair<Node*, Action*>>* execution = nullptr;
	switch (sceneStatus)
	{
	case SCENEBOOT:
		execution = &AnimationSequenceStart;
		break;
	case SCENERUNNING:
		execution = &AnimationSequenceRun;
		break;
	case SCENEEND:
		execution = &AnimationSequenceEnd;
		break;
	default:
		break;
	}
	if (execution != nullptr && execution->size()>0)
	{
		return execution->begin()->second;
	}
	return nullptr;
}

Sprite* BaseScene::createSprite(string imgPath,int tag, string name,Vec2 position, Vec2 anchor )
{
	auto sprite = Sprite::create(imgPath);
	sprite->setTag(tag);
	sprite->setName(name);
	sprite->setAnchorPoint(anchor);
	sprite->setPosition(position);
	sprite->retain();
	nodeStack[nodeTag] = sprite;
	++nodeTag;
	return sprite;
}

void BaseScene::addNode(Node* node)
{
	nodeStack.insert(make_pair(nodeTag, node));
	node->setTag(nodeTag);
	++nodeTag;
}

void BaseScene::update(float delta)
{
	updateSceneStack();
	updateAnimation();
	updateSceneStatus();
}

void BaseScene::updateAnimation()
{
	 list<pair<Node*, Action*>>* execution = nullptr;
	 switch (sceneStatus)
	 {
	 case SCENEBOOT:
		 execution = &AnimationSequenceStart;
		 break;
	 case SCENERUNNING:
		 execution = &AnimationSequenceRun;
		 break;
	 case SCENEEND:
		 execution = &AnimationSequenceEnd;
		 break;
	 default:
		 break;
	 }
	 if (execution == nullptr)
		 return;
	 if (!animStatus)
	 {
		 if (execution->size() > 0)
		 {
			 auto it = execution->begin();
			 if (it->first != nullptr)
			 {
				 it->first->runAction(it->second);
				 animStatus = true;
			 }
		 }
	 }
	 else
	 {
		 auto it = execution->begin();
		 if (it->first->getActionByTag(it->second->getTag()) == nullptr)
		 {
			 animStatus = false;
			 it->second->release();
			 execution->erase(execution->begin());
		 }
	 }
}

void BaseScene::updateSceneStatus()
{
	if (AnimationSequenceStart.size() == 0 && sceneStatus == SCENEBOOT)
	{
		++sceneStatus;
		startScene();
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
	}
	else if (AnimationSequenceRun.size() == 0 && sceneStatus == SCENERUNNING)
	{
		++sceneStatus;
	}
	else if (AnimationSequenceEnd.size() == 0 && sceneStatus == SCENEEND)
	{
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
		endScene();
		++sceneStatus;
	}
}

void BaseScene::problemLoading(std::string filename,BaseScene* name)
{
	std::string strFirst = myType::replaceSubStr("Error while loading: %s",filename);
	std::string strSecond = myType::replaceSubStr("Depending on how you compiled you might have to add 'Resources/' in front of filenames in %s", name->getDescription());
    log((strFirst + strSecond).c_str());
}

void BaseScene::updateSceneStack()
{
	while (sceneStack.size() >= 5)
	{
		sceneStack.erase(sceneStack.begin());
	}
}

void BaseScene::closeApp()
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void BaseScene::replaceScene(Scene* replace)
{
	Director::getInstance()->replaceScene(replace);
}

void BaseScene::pushScene(Scene* push)
{
	Director::getInstance()->pushScene(push);
	sceneStack.push_back(push);
}

void BaseScene::popScene()
{
	Director::getInstance()->popScene();
	sceneStack.erase(sceneStack.end());
}

BaseScene::BaseScene() :visibleSize({ -1,-1 }), origin({-1,-1}),sceneStatus(SCENEBOOT), animStatus(false)
{
	nodeTag = TAGSTARTVALUE;
}

void BaseScene::initAnimation()
{
	for (auto it = AnimationSequenceStart.begin(); it != AnimationSequenceStart.end(); it++)
	{
		if (it->second != nullptr)
			it->second->retain();
	}
	for (auto it = AnimationSequenceRun.begin(); it != AnimationSequenceRun.end(); it++)
	{
		if(it->second != nullptr)
			it->second->retain();
	}
	for (auto it = AnimationSequenceEnd.begin(); it != AnimationSequenceEnd.end(); it++)
	{
		if(it->second!= nullptr)
			it->second->retain();
	}
	for (auto it = AnimationSequenceCustom.begin(); it != AnimationSequenceCustom.end(); it++)
	{
		if(it->second != nullptr)
			it->second->retain();
	}
}

Scene* BaseScene::recallScene(unsigned int pos)
{
	Scene* result = nullptr;
	if (pos >= 5)
	{
		log("couldn't recall any scene as the position requested does not exist");
	}
	else
	{
		unsigned count = 0;
		for (auto it = sceneStack.rbegin(); it != sceneStack.rend(); it++)
		{
			if (count == pos)
			{
				result = *it;
				break;
			}
			++count;
		}
	}
	return result;
}
