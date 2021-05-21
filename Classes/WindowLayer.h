#pragma once
#include "cocos2d.h"
#include <string>
class WindowLayer:
	public cocos2d::Layer
{
public:
#define CLOSED 0 
#define OPENING 1
#define OPENED 2
#define CLOSING 3
	static WindowLayer* create();
	std::string getDescription() const override;

	void addNewString(std::string newStr);

	void enableActorName(bool status,std::string name = "");

CC_CONSTRUCTOR_ACCESS:
	WindowLayer();
	virtual ~WindowLayer();

	virtual bool init() override;
	void setContentSize(const cocos2d::Size& contentSize) override;
	void initInterface();
	void initClipping();

	bool isOpen();
	bool isClosed();
	void open();
	void close();
protected:
	void update(float dt);
	void updateShow(float dt);
	void updateInput(cocos2d::EventMouse* event);

private:
	cocos2d::ClippingNode* clip;
	cocos2d::Label* label;
	cocos2d::Label* labelName;
	cocos2d::Sprite* sign;
	int status;
	bool waiting;
	int segments;
	int radius;
	std::string contents;
	int strCount;
	
};

