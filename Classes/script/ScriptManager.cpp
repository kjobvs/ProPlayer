#include "ScriptManager.h"
#include "../public/CLFunction.h"
#include "ScriptLine.h"
#include "ScriptAudio.h"
#include "ScriptSprite.h"
#include "ScriptScene.h"

using namespace std;
USING_NS_CC;

ScriptManager* ScriptManager::instance = nullptr;

ScriptManager* ScriptManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ScriptManager();
	}
	return instance;
}

Script* ScriptManager::getScriptByTag(int _tag)
{
	return gameScripts[_tag];
}

void ScriptManager::loadScript()
{
	loaded = false;
	fstream fs;
	string filename = FileUtils::getInstance()->fullPathForFilename("Data/script.csv");
	fs.open(filename, ios::in);
	createScript(fs);
	fs.close();
}

void ScriptManager::createScript(fstream& loader)
{
	if (loader.is_open())
	{
		//定义需要用的相关数据并Pre Load properties；
		string buffer;
		list<string> properties;
		list<string> dataLine;
		getline(loader, buffer);

		if (buffer.size() > 0)
		{
			properties = getAttribute(buffer);
		}
		else
		{
			return;
		}
		// 开始读取具体数据；
		while (!loader.eof())
		{
			getline(loader, buffer);
			dataLine = getAttribute(buffer);
			if (dataLine.size() > 0)
			{
				//根据type创建对象；
				Script* script;
				map<string, string> dataGrid = getDataGrid(properties, dataLine);
				switch (myType::turnNum(dataGrid["type"]) / 100)
				{
				case 1:
					script = new ScriptLine();
					break;
				case 2:
					script = new ScriptSprite();
					break;
				case 3:
					script = new ScriptScene();
					break;
				case 4:
					script = new ScriptAudio();
					break;
				default:
					continue;
					break;
				}
				script->setContents(dataGrid);
				script->setType(myType::turnNum(dataGrid["type"]));
				script->setTag(myType::turnNum(dataGrid["tag"]));
				script->setDescription(dataGrid["description"]);
				gameScripts.insert(make_pair(script->getTag(), script));
			}
		}
	}
	loaded = true;
}

list<string> ScriptManager::getAttribute(string data)
{
	list<string> result;
	if (data.size() == 0)
	{
		return result;
	}
	while (data.find(',') != string::npos)
	{
		data.substr(0, data.find(',')).size() > 0 ? result.push_back(data.substr(0, data.find(','))) : result.push_back("");
		data.erase(0, data.find(',') + 1);
	}
	data.size() > 0 ? result.push_back(data) : result.push_back("");
	return result;
}

map<string, string> ScriptManager::getDataGrid(list<string> &_attr, list<string> &_data)
{
	map<string, string> result;
	for (auto itP = _attr.begin(), itD = _data.begin(); itP != _attr.end(); ++itP, ++itD)
	{
		result.insert(make_pair(*itP, *itD));
	}
	return result;
}

ScriptManager::ScriptManager():loaded(false)
{
}

ScriptManager::ScriptManager(ScriptManager& copy)
{
	loaded = copy.loaded;
	gameScripts = copy.gameScripts;
	instance=copy.instance;
}