#include "TouchLayer.h"

using namespace std;
USING_NS_CC;

TouchLayer::TouchLayer()
{
}


TouchLayer::~TouchLayer()
{
}

TouchLayer* TouchLayer::create()
{
	auto pRet = new TouchLayer();
	if (pRet != nullptr && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool TouchLayer::init()
{
	if (!Layer::init())
		return false;
	this->setSwallowsTouches(true);
	return true;
}

string TouchLayer::getDescription() const
{
	return "BaseTouchLayer";
}

