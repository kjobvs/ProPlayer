#pragma once
#include "Actor.h"
#include "GameData.h"
#include <list>
class Line:
	public GameData
{
public:
	static Line* create();
	void setActor(Actor* _actor);
	Actor* getActor();
	void setWord(std::string _word);
	std::string getWord();
	void setMood(int _mood);
	void setActorName(std::string name);
	std::string getActorName();
	void setType(int _type);
	void setAttribute(std::list<int> _attr);
	int returnMood();
private:
	Line();
	~Line();
	Actor* actor;
	std::list<int> attributes;
	std::string actorName;
	int mood;
	int type;
	std::string words;
	static int lineTag;
};

