#pragma once
#include "ImageLayer.h"
class BackGroundLayer:
	public ImageLayer
{
public:
	static BackGroundLayer* create();
	static BackGroundLayer* create(std::string _filename);
	bool init() override;
CC_CONSTRUCTOR_ACCESS:
	BackGroundLayer();
	virtual ~BackGroundLayer();
};

