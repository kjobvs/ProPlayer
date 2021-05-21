#pragma once
#include "Script.h"
#include <map>
#include <list>
class ScriptScene:
	public Script
{
public:
	ScriptScene();
	void setContents(std::map<std::string, std::string> contents) override;
	int start() override;

	int sceneSwitch();
	int sceneEffect();
	void loadSceneSwitch(std::map<std::string, std::string> _data);
	void loadSceneEffect(std::map<std::string, std::string> _data);
protected:
	void createSnow();
	void createRain();
private:
	std::string pathFile;
	std::list<int> weather;	
	std::string main;
	std::map<int,int(ScriptScene::*)()> functionList;
	std::map<int,void(ScriptScene::*)(std::map<std::string,std::string>)> loadFunction;
	std::map<int, void(ScriptScene::*)()> sceneEffects;

};

