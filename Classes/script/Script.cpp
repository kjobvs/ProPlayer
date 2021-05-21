#include "Script.h"

using namespace std;

void Script::setTag(int _tag)
{
	tag = _tag;
}

int Script::getTag()
{
	return tag;
}

int Script::getType()
{
	return type;
}

string Script::getDescription()
{
	return description;
}

void Script::setType(int _type)
{
	type = _type;
}

void Script::setDescription(string _des)
{
	description = _des;
}
