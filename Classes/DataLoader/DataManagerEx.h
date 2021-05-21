#pragma once
#include "cocos2d.h"
#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <tuple>
#include "Actor.h"
#include "Line.h"



class DataManagerEx:
	public cocos2d::Ref
{
public:
	static DataManagerEx* getInstance();
	void loadFile();

	int getLoadingStatus();
	bool isLoaded();

	void addLine(Line* line);

	Actor* getActorByTag(int _tag);
	Actor* getActorByName(std::string _name);
	Line* getLineByTag(int _tag);
protected:
	std::list<std::string> getAttribute(std::string data);
	std::list<int> getNumbers(std::string data);
	std::map <std::string, std::string> getDataGrid(std::list<std::string> &_attr, std::list<std::string> &_data);
private:
	static DataManagerEx* ptr;

	std::map<int, Actor*> gameActors;
	std::map<int, GameData*> gameScenes;
	std::map<int, GameData*> gameItems;
	std::map<int, GameData*> gameImages;
	std::map<int, Line*> gameLines;


	
	std::map<std::string, void(DataManagerEx::*)(std::fstream &)> index;

	void createActor(std::fstream& loader);
	void createScene(std::fstream& loader);
	void createItem(std::fstream& loader);
	void createImage(std::fstream& loader);

	int loadingProgress;
	DataManagerEx();
};

