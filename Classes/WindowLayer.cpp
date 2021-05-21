#include "WindowLayer.h"
#include "public/CLFunction.h"
#include "GameControl/GameControl.h"

USING_NS_CC;
using namespace std;

#define STR myType::GBKToUTF8

WindowLayer::WindowLayer() :status(CLOSED), segments(1500), radius(10.0f), waiting(false)
{
}

WindowLayer::~WindowLayer()
{
}

void WindowLayer::setContentSize(const Size& contentSize)
{
	Layer::setContentSize(contentSize);
	initInterface();
}

bool WindowLayer::init()
{
	status = CLOSED;
	_ignoreAnchorPointForPosition = false;
	setAnchorPoint(Vec2(0, 0));
	setContentSize(Director::getInstance()->getVisibleSize()*0.4);
	auto scale = ScaleTo::create(0.01f, 0.01f);
	this->runAction(scale);
	this->scheduleUpdate();
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(WindowLayer::updateInput, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void WindowLayer::initInterface()
{
	removeAllChildren();
	//创建主窗口区域；
	initClipping();
	//创建文字区；
	label = Label::createWithTTF("","fonts/FZLTBlack.ttf",10);
	label->setDimensions(this->getContentSize().width*0.85,this->getContentSize().height*0.75);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setName("word");
	label->setPosition(Vec2(this->getContentSize().width/2,label->getDimensions().height/2));
	this->getChildByName("mainWindow")->addChild(label);
	//创建nameWindow;
	auto sprite = Sprite::createWithSpriteFrameName("window00.png");
	Layer::setContentSize(Size(this->getBoundingBox().size.width, this->getBoundingBox().size.height + sprite->getContentSize().height *0.6));
	sprite->setAnchorPoint(Vec2(0,0));
	sprite->setPosition(Vec2(0, this->getBoundingBox().size.height-sprite->getBoundingBox().size.height));
	sprite->setName("nameWindow");
	addChild(sprite);
	//创建name文字区；
	labelName = Label::createWithTTF("", "fonts/FZLTBlack.ttf", 10);
	labelName->setDimensions(sprite->getContentSize().width*0.9,sprite->getContentSize().height*0.9);
	labelName->setAnchorPoint(Vec2(0.5, 0.5));
	labelName->setName("name");
	labelName->setPosition(sprite->getContentSize() / 2);
	labelName->setVerticalAlignment(TextVAlignment::CENTER);
	labelName->setHorizontalAlignment(TextHAlignment::LEFT);
	sprite->addChild(labelName);
	//创建waiting光标；
	auto animation = Animation::create();
	auto temp = Sprite::create("img/animation/000.png");
	auto width = temp->getContentSize().width / 4;
	auto height = temp->getContentSize().height / 2;
	sign = Sprite::create("img/animation/000.png",Rect(0,0,width,height));
	for (auto i = 0; i < 2; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			animation->addSpriteFrame(SpriteFrame::create("img/animation/000.png",Rect(width*j,height*i,width,height)));
		}
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	sign->runAction(Animate::create(animation));
	this->addChild(sign);
	sign->setAnchorPoint(Vec2(1, 0));
	sign->setPosition(Vec2(this->getBoundingBox().size.width*0.95,this->getBoundingBox().size.height*0.05));
	sign->setVisible(waiting);
}

void WindowLayer::initClipping()
{
	//创建baseTexture;
	auto texture = Sprite::createWithSpriteFrameName("window01.png");
	auto width = texture->getBoundingBox().size.width;
	auto height = texture->getBoundingBox().size.height;
	auto layer = Layer::create();
	layer->setContentSize(this->getContentSize());
	layer->setPosition(0, 0);
	for (size_t i = 0; i <= this->getBoundingBox().size.width / width + 1; i++)
	{
		auto sprite = Sprite::createWithSpriteFrameName("window01.png");
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(width*i, 0);
		sprite->setScaleY(2.04);
		layer->addChild(sprite);
	}
	//4/1圆的位置；
	const float coef = 0.5f * (float)M_PI / segments;
	Point * vertices = new Point[segments + 1];
	Point * thisVertices = vertices;
	for (unsigned int i = 0; i <= segments; ++i, ++thisVertices)
	{
		float rads = (segments - i)*coef;
		thisVertices->x = (int)(radius * sinf(rads));
		thisVertices->y = (int)(radius * cosf(rads));
	}

	Point tagCenter;
	float minX = this->getBoundingBox().getMinX();
	float maxX = this->getBoundingBox().getMaxX();
	float minY = this->getBoundingBox().getMinY();
	float maxY = this->getBoundingBox().getMaxY();

	unsigned int dwPolygonPtMax = (segments + 1) * 4;
	Point * pPolygonPtArr = new Point[dwPolygonPtMax];
	Point * thisPolygonPt = pPolygonPtArr;
	int aa = 0;
	//左上角
	tagCenter.x = minX + radius;
	tagCenter.y = maxY - radius;
	thisVertices = vertices;
	for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices)
	{
		thisPolygonPt->x = tagCenter.x - thisVertices->x;
		thisPolygonPt->y = tagCenter.y + thisVertices->y;
		++aa;
	}
	//右上角
	tagCenter.x = maxX - radius;
	tagCenter.y = maxY - radius;
	thisVertices = vertices + segments;
	for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices)
	{
		thisPolygonPt->x = tagCenter.x + thisVertices->x;
		thisPolygonPt->y = tagCenter.y + thisVertices->y;
		++aa;
	}
	//右下角
	tagCenter.x = maxX - radius;
	tagCenter.y = minY + radius;
	thisVertices = vertices;
	for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices)
	{
		thisPolygonPt->x = tagCenter.x + thisVertices->x;
		thisPolygonPt->y = tagCenter.y - thisVertices->y;
		++aa;
	}
	//左下角
	tagCenter.x = minX + radius;
	tagCenter.y = minY + radius;
	thisVertices = vertices + segments;
	for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices)
	{
		thisPolygonPt->x = tagCenter.x - thisVertices->x;
		thisPolygonPt->y = tagCenter.y - thisVertices->y;
		++aa;
	}
	auto draw = DrawNode::create();
	draw->clear();
	draw->drawSolidPoly(pPolygonPtArr, dwPolygonPtMax, Color4F(0,0,0,1.0f));
	CC_SAFE_DELETE_ARRAY(vertices);
	CC_SAFE_DELETE_ARRAY(pPolygonPtArr);
	auto clip = ClippingNode::create();
	clip->setStencil(draw);
	clip->addChild(layer);
	clip->setName("mainWindow");
	clip->setAnchorPoint(Vec2(0, 0));
	clip->setPosition(Vec2(0, 0));
	addChild(clip);
}

WindowLayer* WindowLayer::create()
{
	WindowLayer* ret = new (std::nothrow) WindowLayer();
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

string WindowLayer::getDescription() const
{
	return StringUtils::format("<WindowLayer | Tag = %d>", _tag);
}

bool WindowLayer::isOpen()
{
	return status == OPENED;
}

bool WindowLayer::isClosed()
{
	return status == CLOSED;
}

void WindowLayer::open()
{
	if (this->getActionByTag(0) == nullptr)
	{
		auto delay = DelayTime::create(1.0f);
		auto scale = ScaleTo::create(0.3f, 1.0f);
		auto ease = EaseIn::create(scale, 3.0f);
		auto delayAfter = DelayTime::create(0.6f);
		auto seq = Sequence::create(delay, ease,delayAfter, CallFunc::create([this]() {this->status = OPENED; }), nullptr);
		seq->setTag(0);
		this->runAction(seq);
		status = OPENING;
	}
}

void WindowLayer::close()
{
	if (this->getActionByTag(1) == nullptr)
	{
		auto scale = ScaleTo::create(0.2f, 0.001f);
		auto ease = EaseOut::create(scale, 3.0f);
		auto seq = Sequence::create(ease,CallFunc::create([this]() {this->status = CLOSED; }), nullptr);
		seq->setTag(0);
		this->runAction(seq);
		status = CLOSING;
		this->unschedule(schedule_selector(WindowLayer::updateShow));
	}
}

void WindowLayer::enableActorName(bool status, string name)
{
	if (status)
	{
		this->getChildByName("nameWindow")->setVisible(true);
		labelName->setString(STR(name));
	}

	else
		this->getChildByName("nameWindow")->setVisible(false);
}

void WindowLayer::addNewString(string newStr)
{
	contents = newStr;
	strCount = 0;
    schedule(schedule_selector(WindowLayer::updateShow),GameControl::getInstance()->getTextSpeed(), kRepeatForever, 0);
}

void WindowLayer::update(float dt)
{
	if (sign->isVisible() != waiting)
		sign->setVisible(waiting);
}

void WindowLayer::updateShow(float dt)
{
	if (!isOpen())
	{
		open();
	}
	if (this->getActionByTag(0) == nullptr)
	{
		if (strCount <= contents.size())
			label->setString(STR(contents.substr(0, strCount++)));
		else
			waiting = true;
	}

}

void WindowLayer::updateInput(EventMouse* event)
{
	if (!isOpen())
		return;
	if (waiting)
	{
		waiting = false;
		contents.clear();
		GameControl::getInstance()->advanceProgress();
	}
	else
	{
		strCount = contents.size();
		label->setString(STR(contents));
		waiting = true;
	}
}
