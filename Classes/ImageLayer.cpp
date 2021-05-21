#include "ImageLayer.h"

using namespace std;
USING_NS_CC;

ImageLayer* ImageLayer::create()
{
	ImageLayer* ret = new (std::nothrow) ImageLayer();
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

ImageLayer::ImageLayer():spriteTag(0),particleTag(100)
{
}

ImageLayer::~ImageLayer()
{
}

bool ImageLayer::init()
{
	if (!Layer::init())
		return false;
	return true;
}

string ImageLayer::getDescription() const
{
	return Layer::getDescription();
}

void ImageLayer::addChild(Node * child)
{
	Layer::addChild(child);
}

void ImageLayer::addChild(Node * child, int zOrder)
{
	Layer::addChild(child, zOrder);
}

void ImageLayer::addChild(Node * child, int zOrder, int tag)
{
	CCASSERT(dynamic_cast<Sprite*>(child) != nullptr||dynamic_cast<ParticleSystem*>(child)!= nullptr, "Image Layer only Supports sprites and particles");
	if (dynamic_cast<Sprite*>(child) != nullptr)
	{
		sprites.push_back(dynamic_cast<Sprite*>(child));
		Layer::addChild(child, zOrder, tag);
	}
	else
	{
		particles.push_back(dynamic_cast<ParticleSystem*>(child));
		Layer::addChild(child, 500+zOrder, tag);
	}

}

void ImageLayer::addChild(Node * child, int zOrder, const std::string &name)
{
	CCASSERT(dynamic_cast<Sprite*>(child) != nullptr || dynamic_cast<ParticleSystem*>(child) != nullptr, "Image Layer only Supports sprites and particles");
	if (dynamic_cast<Sprite*>(child) != nullptr)
	{
		sprites.push_back(dynamic_cast<Sprite*>(child));
		Layer::addChild(child, zOrder, name);
	}
	else
	{
		particles.push_back(dynamic_cast<ParticleSystem*>(child));
		Layer::addChild(child, 500 + zOrder, name);
	}
}

void ImageLayer::removeChild(Node* child, bool cleanup)
{
	if (dynamic_cast<Sprite*>(child) != nullptr)
	{
		sprites.erase(find(sprites.begin(), sprites.end(), child));
	}
	else if(dynamic_cast<ParticleSystem*>(child) != nullptr)
	{
		particles.erase(find(particles.begin(), particles.end(), child));
	}
	Layer::removeChild(child, cleanup);
}