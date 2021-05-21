#include "BackGroundLayer.h"

using namespace std;
USING_NS_CC;

BackGroundLayer* BackGroundLayer::create()
{
	BackGroundLayer* ret = new (std::nothrow) BackGroundLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

BackGroundLayer* BackGroundLayer::create(string _filename)
{
	auto pRet = BackGroundLayer::create();
	if (pRet != nullptr)
	{
		auto sprite = Sprite::create(_filename);
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		sprite->setPosition(pRet->getContentSize().width / 2, pRet->getContentSize().height / 2);
		pRet->addChild(sprite, 0, 0);
	}
	return pRet;
}

BackGroundLayer::BackGroundLayer()
{
}

BackGroundLayer::~BackGroundLayer()
{
}

bool BackGroundLayer::init()
{
	if (!ImageLayer::init())
		return false;
	return true;
}