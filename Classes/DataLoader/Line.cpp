#include "Line.h"
#include "../public/CLFunction.h"

#define STR myType::GBKToUTF8

using namespace std;
USING_NS_CC;

int Line::lineTag = 20000000;

Line* Line::create()
{
	auto ptr = new Line();
	if (ptr != nullptr)
		ptr->autorelease();
	return ptr;
}

void Line::setActor(Actor* _actor)
{
	actor = _actor;
}

void Line::setAttribute(list<int> _attr)
{
	attributes = _attr;
}
void Line::setActorName(string name)
{
	actorName = name;
}

string Line::getActorName()
{
	if (find(attributes.begin(), attributes.end(), 101) != attributes.end())
		return "???";
	else
		return actorName;
}

void Line::setWord(string _word)
{
	words = _word;
}

void Line::setType(int _type)
{
	type = _type % 100;
}

void Line::setMood(int _mood)
{
	mood = _mood;
}

Line::Line():actor(nullptr),words(""),mood(0)
{
	setTag(lineTag++);
}

Line::~Line()
{
}

Actor* Line::getActor()
{
	return  actor;
}

string Line::getWord()
{
	string result = words;
	if (find(attributes.begin(), attributes.end(), 101) != attributes.end())
	{
		result.push_back(')');
		string temp = "(";
		result = temp + result;
	}
	return result;
}

int Line::returnMood()
{
	return mood;
}