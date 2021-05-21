#include "ScriptLine.h"
#include "../DataLoader/DataManagerEx.h"
#include "../DataLoader/Line.h"
#include "../public/CLFunction.h"


using namespace std;
USING_NS_CC;

void ScriptLine::setContents(map<string, string> contents)
{
	if (line == nullptr)
	{
		line = Line::create();
		line->retain();
	}
	line->setMood(myType::turnNum(contents["mood"]));
	line->setWord(contents["contents"]);
 	line->setActor(DataManagerEx::getInstance()->getActorByName(contents["name"]));
	line->setName("line");
	line->setActorName(contents["name"]);
	line->setType(100);
	line->setAttribute(myData::getListNum(contents["type"]));
	DataManagerEx::getInstance()->addLine(line);
}

int ScriptLine::start()
{
	if (line != nullptr)
	{
		Director::getInstance()->getRunningScene()->addChild(line,NULL,line->getTag());
	}
	return 1;
}

Line* ScriptLine::getLine()
{
	return line;
}