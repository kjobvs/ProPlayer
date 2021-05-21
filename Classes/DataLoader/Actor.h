#pragma once
#include "GameData.h"

class Actor:
	public GameData
{
public:
	cocos2d::Sprite* getSprite();
	void changeMood();

	void setAge(unsigned int _age);
	unsigned int getAge();
	void setHeight(unsigned int _height);
	unsigned int getHeight();
	void setWeight(double _w);
	std::string getWeightInS(std::string unit ="kg");
	void setName(std::string _name);
	std::string getName();
	void setPath(std::string pathName);
	std::string getPath();
	void setSex(int _sex);
	char getSex();
	bool isVisible();
	void setVisible(bool status);
	cocos2d::Vec2 getPosition();
	void setPosition(cocos2d::Vec2 pos);

	void clearFace();

	void addAvatar(int tag);
	void addAvatar(std::list<int> tag);

	static Actor* create();
protected:
	unsigned int age;
	unsigned int height;
	double weight;
	std::string name;
	std::string imgPath;
	std::list<int> gameID;
	cocos2d::Sprite* face;
	int mood;
	bool sex;
	bool visible;
	cocos2d::Vec2 position;
	Actor();
};

