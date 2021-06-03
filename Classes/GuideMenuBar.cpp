#include "GuideMenuBar.h"

using namespace std;
USING_NS_CC;

GuideMenuBar::GuideMenuBar()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

}


GuideMenuBar::~GuideMenuBar()
{
}

bool GuideMenuBar::init()
{
	if (!TouchLayer::init())
		return false;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	auto backBar = DrawNode::create();
	vector<Vec2> verts;
	verts.push_back(Vec2(visibleSize.width*0.4, visibleSize.height*0.1));
	verts.push_back(Vec2(visibleSize.width, visibleSize.height*0.1));
	verts.push_back(Vec2(visibleSize.width, 0));
	verts.push_back(Vec2(visibleSize.width*0.5, 0));
	verts.push_back(Vec2(visibleSize.width*0.4, visibleSize.height*0.08));
	verts.push_back(Vec2(0, visibleSize.height*0.08));
	verts.push_back(Vec2(0, visibleSize.height*0.1));
	backBar->drawSolidPoly(&verts[0], verts.size(), Color4F(0, 0, 0, 0.5));
	backBar->setName("backBar");
	backBar->setPosition(Vec2(0, visibleSize.height));
	backBar->setContentSize(Size(visibleSize.width, visibleSize.height*0.167));
	this->addChild(backBar);
	initInput();
	initButtons();
	return true;
}

void GuideMenuBar::initButtons()
{
	float Bheight = visibleSize.height* 0.1;
	float Bwidth = visibleSize.width*0.5;
	initFastSave();
}

void GuideMenuBar::initFastSave()
{

}

void GuideMenuBar::initInput()
{
	auto guideBarTouch = EventListenerMouse::create();

	guideBarTouch->onMouseMove = [=](EventMouse* event) {
		Vec2 pos(event->getCursorX(), event->getCursorY());
		auto rect = event->getCurrentTarget()->getBoundingBox();
		if (rect.containsPoint(pos))
		{
			if (rect.getMaxY() > visibleSize.height*1.01)
			{
				auto ease = EaseIn::create(MoveTo::create(0.6f, Vec2(0, visibleSize.height*0.9)), 2.0f);
				ease->setTag(0);
				auto target = event->getCurrentTarget();
				if (target->getActionByTag(0) == nullptr)
					event->getCurrentTarget()->runAction(ease);
			}
		}
		if (!rect.containsPoint(pos))
		{
			if (event->getCurrentTarget()->getActionByTag(0) == nullptr)
			{
				auto ease = EaseOut::create(MoveTo::create(0.4f, Vec2(0, visibleSize.height*0.96)), 2.0f);
				ease->setTag(1);
				auto target = event->getCurrentTarget();
				if (target->getActionByTag(1) == nullptr)
					event->getCurrentTarget()->runAction(ease);
			}
		}
	};
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto target = this->getChildByName("backBar");
	dispatcher->addEventListenerWithSceneGraphPriority(guideBarTouch, target);
}

string GuideMenuBar::getDescription() const
{
	return "GuideMenuBar";
}