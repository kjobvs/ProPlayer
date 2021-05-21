#pragma once
#include "cocos2d.h"
#include "Script.h"
#include <fstream>
#include <map>

class ScriptManager:
	public cocos2d::Ref
{
public:
	static ScriptManager* getInstance();
	
	Script* getScriptByTag(int _tag);

	void loadScript();

protected:
	std::list<std::string> getAttribute(std::string data);
	std::map <std::string, std::string> getDataGrid(std::list<std::string> &_attr, std::list<std::string> &_data);
private:
	static ScriptManager* instance;
	bool loaded;
	std::map<int, Script*> gameScripts;

	void createScript(std::fstream& loader);

	ScriptManager();
	ScriptManager(ScriptManager & copy);


};

