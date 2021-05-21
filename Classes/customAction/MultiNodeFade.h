#pragma once
#include "MultiNode.h"

class MultiNodeFadeOut:
	public cocos2d::FadeOut,public MultiNode
{
public:
	static MultiNodeFadeOut* create(float d);
	void update(float time) override;
CC_CONSTRUCTOR_ACCESS:
	MultiNodeFadeOut() : _reverseAction(nullptr) {}
	virtual ~MultiNodeFadeOut() {}
private:
	CC_DISALLOW_COPY_AND_ASSIGN(MultiNodeFadeOut);
	FadeTo* _reverseAction;
};


class MultiNodeFadeIn:
	public cocos2d::FadeIn,public MultiNode
{
public:
	static MultiNodeFadeIn* create(float d);
	// overrides;
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	MultiNodeFadeIn() : _reverseAction(nullptr) {}
	virtual ~MultiNodeFadeIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(MultiNodeFadeIn);
	FadeTo* _reverseAction;
};

