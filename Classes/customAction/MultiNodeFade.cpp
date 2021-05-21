#include "MultiNodeFade.h"

USING_NS_CC;


MultiNodeFadeIn* MultiNodeFadeIn::create(float d)
{
	MultiNodeFadeIn* mtnFadeIn = new (std::nothrow) MultiNodeFadeIn();
	if (mtnFadeIn && mtnFadeIn->initWithDuration(d, 255))
	{
		mtnFadeIn->autorelease();
		return mtnFadeIn;
	}
	delete mtnFadeIn;
	return nullptr;
}

void MultiNodeFadeIn::update(float time)
{
	for (auto it = targets.begin(); it != targets.end(); ++it)
	{
		_target = *it;
		if (_target)
		{
			_target->setOpacity((GLubyte)(fromOpacity[it - targets.begin()] + (toOpacity[it-targets.begin()] - fromOpacity[it - targets.begin()]) * time));
		}
	}
	_target = nullptr;
}

MultiNodeFadeOut* MultiNodeFadeOut::create(float d)
{
	MultiNodeFadeOut* mtnFadeOut = new (std::nothrow) MultiNodeFadeOut();
	if (mtnFadeOut && mtnFadeOut->initWithDuration(d, 0))
	{
		mtnFadeOut->autorelease();
		return mtnFadeOut;
	}
	delete mtnFadeOut;
	return nullptr;
}

void MultiNodeFadeOut::update(float time)
{
	for (auto it = targets.begin(); it != targets.end(); ++it)
	{
		_target = *it;
		if (_target)
		{
			_target->setOpacity((GLubyte)(fromOpacity[it-targets.begin()] + (toOpacity[it-targets.begin()] - fromOpacity[it-targets.begin()]) * time));
		}
	}
	_target = nullptr;
}