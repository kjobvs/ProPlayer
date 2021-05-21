#pragma once
#include "cocos2d.h"
class ImageLayer:
	public cocos2d::Layer
{
public:
	static ImageLayer* create();
	std::string getDescription() const override;
	bool init() override;
	void addChild(Node * child) override;
	void addChild(Node * child, int zOrder) override;
	void addChild(Node * child, int zOrder, int tag) override;
	void addChild(Node * child, int zOrder, const std::string &name) override;

	void removeChild(Node* child, bool cleanup = true) override;
CC_CONSTRUCTOR_ACCESS:
	ImageLayer();
	virtual ~ImageLayer();

protected:
	std::list<cocos2d::Sprite*> sprites;
	std::list<cocos2d::ParticleSystem*> particles;
	std::list<std::string> spritesFilePath;

	int spriteTag;
	int particleTag;
};

