#include "Actor.h"
#include "../public/myType.h"
#include <iostream>
#include <sstream>

using namespace std;
USING_NS_CC;

#define ENDLINE ";";



Actor* Actor::create()
{
	return new Actor();
}

Sprite* Actor::getSprite()
{
	if (face == nullptr)
	{
		face = Sprite::create(imgPath);
		if (face != nullptr)
		{
			face->setAnchorPoint(Vec2(0, 1));
			face->setName(name);
			face->setTag(tag);
		}
	}
	return face;
}

void Actor::changeMood()
{
}

void Actor::setAge(unsigned int _age)
{
	age = _age;
}

unsigned int Actor::getAge()
{
	return age;
}

void Actor::setHeight(unsigned int _height)
{
	height = _height;
}

unsigned int Actor::getHeight()
{
	return height;
}

void Actor::setWeight(double _w)
{
	weight = _w;
}

std::string Actor::getWeightInS(string unit)
{
    if (unit == "lbs")
		return myType::turnString(weight*2.2065) + "lbs";
	else if (unit == "½ï")
		return myType::turnString(weight * 2) + "½ï";
	return myType::turnString(weight) + "kg";
}


void Actor::setName(string _name)
{
	name = _name;
}

string Actor::getName()
{
	return name;
}

void Actor::setPath(string pathName)
{
	
	imgPath = pathName;
}

string Actor::getPath()
{
	return imgPath;
}

void Actor::setSex(int _sex)
{
	sex = _sex;
}

char Actor::getSex()
{
	if (sex)
	{
		return 'm';
	}
	else
	{
		return 'f';
	}
}

bool Actor::isVisible()
{
	return visible;
}

void Actor::setVisible(bool status)
{
	visible = status;
}

Vec2 Actor::getPosition()
{
	return position;
}

void Actor::setPosition(Vec2 pos)
{
	position = pos;
	if(face != nullptr)
		face->setPosition(position);
}

Actor::Actor():age(-1),height(-1),name(""),mood(0),imgPath(""),sex(true),face(nullptr)
{
}

void Actor::clearFace()
{
	face = nullptr;
}


void Actor::addAvatar(int tag)
{
	gameID.push_back(tag);
}

void Actor::addAvatar(list<int> tag)
{
	for (auto it = tag.begin(); it != tag.end(); it++)
	{
		gameID.push_back(*it);
	}
}