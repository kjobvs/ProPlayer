#include "ScriptSprite.h"
#include "GameControl\GameControl.h"

using namespace std;
USING_NS_CC;

void ScriptSprite::setContents(map<string, string> contents)
{
	switch (type % 100)
	{
	case 0:
		pathFile = "img/CG/";
		break;
	case 2:
		pathFile = "img/item/";
		break;
	}
	if (contents["contents"] != "")
	{
		pathFile += contents["contents"] + ".png";
	}
	else
	{
		pathFile = "";
	}
	sprite = Sprite::create(pathFile);
	if (sprite != nullptr)
		sprite->retain();
}

int ScriptSprite::start()
{
	int result = -1;
	if (type % 100 == 0)
	{
		result = addCG();
	}
	else if (type % 100 == 1)
	{
		result = removeCG();

	}
	else if(type%100 == 2)
	{
		result =addItem();
	}
	return result;
}

int ScriptSprite::closeDialog()
{
	int result = -1;
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getChildByName("CGLayer") != nullptr)
	{
		if (scene->getChildByName("Dialog") != nullptr)
			scene->removeChildByName("Dialog");
		else
			result = 0;
	}
	return result;
}

int ScriptSprite::addCG()
{
	int result = 0;
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("CGLayer");
	if (layer != nullptr)
	{
		result = closeDialog();
		if (result == -1)
			return result;
		if (layer->getChildByName("CG") != nullptr)
			layer->removeChildByName("CG");
		sprite->setName("CG");
		sprite->setOpacity(0);
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		sprite->setPosition(Vec2(layer->getContentSize().width/2, layer->getContentSize().height/2));
		layer->addChild(sprite);
		auto fade = FadeIn::create(2.0f);
		auto easeFade = EaseIn::create(fade, 2.0f);
		auto seq = Sequence::create(easeFade, CallFunc::create([=]() {GameControl::getInstance()->advanceProgress(); }), nullptr);
		sprite->runAction(seq);
		result = 1;
	}
	return result;
}

int ScriptSprite::removeCG()
{
	int result = 0;
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("CGLayer");
	if (layer != nullptr)
	{
		result = closeDialog();
		if (result == -1)
			return result;
		auto fade = FadeOut::create(2.0f);
		auto easeFade = EaseOut::create(fade, 2.0f);
		auto seq = Sequence::create(easeFade, CallFunc::create(
			[=]() {
			if (layer->getChildByName("CG") != nullptr)
				layer->getChildByName("CG")->setVisible(false);
			GameControl::getInstance()->advanceProgress();
		}),
			nullptr);
		if (layer->getChildByName("CG") != nullptr)
		{
			layer->getChildByName("CG")->runAction(seq);
			result = 1;
		}
	}
	return result;
}

int ScriptSprite::addItem()
{
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("ItemLayer");
	if (layer != nullptr)
	{
		if (layer->getChildByName("item") != nullptr)
			layer->removeChildByName("Item");
		sprite->setName("item");
		layer->addChild(sprite);
	}
	return 0;
}

int ScriptSprite::removeItem()
{
	return 0;
}