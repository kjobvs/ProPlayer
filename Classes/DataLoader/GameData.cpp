#include "GameData.h"

using namespace std;

void GameData::setTag(int _tag)
{
	tag = _tag;
}

int GameData::getTag()
{
	return tag;
}

void GameData::setDescription(string des)
{
	description = des;
}

string GameData::getDescription()
{
	return description;
}