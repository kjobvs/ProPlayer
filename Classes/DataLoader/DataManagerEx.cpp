#include "DataManagerEx.h"
#include <iostream>
#include "../public/CLFunction.h"

#define STR myType::GBKToUTF8
using namespace std;
USING_NS_CC;

#define DEBUG cout << "success" << endl;system("pause");
#define SEPERATOR '|'

DataManagerEx* DataManagerEx::ptr = nullptr;

DataManagerEx* DataManagerEx::getInstance()
{
	if (ptr == nullptr)
	{
		ptr = new DataManagerEx();
	}
	return ptr;
}

Actor* DataManagerEx::getActorByTag(int _tag)
{
	if (gameActors.find(_tag)!= gameActors.end())
		return gameActors[_tag];
	return nullptr;
}

Actor* DataManagerEx::getActorByName(string _name)
{
	for (auto it = gameActors.begin(); it != gameActors.end(); it++)
	{
		if (it->second->getName() == _name)
			return it->second;
	}
	return nullptr;
}

Line* DataManagerEx::getLineByTag(int _tag)
{
	return gameLines[_tag];
}

void DataManagerEx::addLine(Line* line)
{
	gameLines[line->getTag()] = line;
}

DataManagerEx::DataManagerEx():loadingProgress(-1)
{
	index["actor"] = &DataManagerEx::createActor;
	index["scene"] = &DataManagerEx::createScene;
	index["item"] = &DataManagerEx::createItem;
	index["image"] = &DataManagerEx::createImage;
}

int DataManagerEx::getLoadingStatus()
{
	return loadingProgress;
}

bool DataManagerEx::isLoaded()
{
	return (loadingProgress == index.size());
}

list<string> DataManagerEx::getAttribute(string data)
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

list<int> DataManagerEx::getNumbers(string data)
{
	list<int> result;

	if(data.size() == 0)
	{
		return result;
	}
	for (auto it = data.begin(); it != data.end();)
	{
		if (*it == '"')
			it = data.erase(it);
		else
			++it;
	}

	while (data.find(SEPERATOR) != string::npos)
	{
		result.push_back(myType::turnNum(data.substr(0, data.find(SEPERATOR))));
		data.erase(0, data.find(SEPERATOR) + 1);
	}
	if (data.size() > 0)
		result.push_back(myType::turnNum(data));
	return result;
}

map<string, string> DataManagerEx::getDataGrid(list<string> &_attr, list<string> &_data)
{
	map<string, string> result;
	for (auto itP = _attr.begin(), itD = _data.begin(); itP != _attr.end(); ++itP, ++itD)
	{
		result.insert(make_pair(*itP, *itD));
	}
	return result;
}

void DataManagerEx::loadFile()
{
	loadingProgress = 0;
	fstream fs;
	for (auto it = index.begin(); it != index.end(); it++)
	{
		string filename = it->first;
		string path = FileUtils::getInstance()->fullPathForFilename("Data/"+filename + ".csv");
		fs.open(path, ios::in);
		(this->*(it->second))(fs);
		fs.close();
	}
}

void DataManagerEx::createActor(fstream& loader)
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
				auto actor = Actor::create();
				for (auto itP = properties.begin(), itD = dataLine.begin(); itP != properties.end(); ++itP, ++itD)
				{
					if (*itP == "tag")
						actor->setTag(myType::turnNum(*itD));
					else if (*itP == "sex")
						actor->setSex(myType::turnNum(*itD));
					else if (*itP == "age")
						actor->setAge(myType::turnNum(*itD));
					else if (*itP == "name")
						actor->setName(*itD);
					else if (*itP == "height")
						actor->setHeight(myType::turnNum(*itD));
					else if (*itP == "imgPath" && itD->size()>0)
						(*itD).size()>0? actor->setPath("img/portrait/"+*itD+".png"): actor->setPath("");
					else if (*itP == "description")
						actor->setDescription(*itD);
					else if (*itP == "gameID")
						actor->addAvatar(getNumbers(*itD));
					else if (*itP == "weight")
						actor->setWeight(myType::turnNum(*itD));
				}
				gameActors.insert(make_pair(actor->getTag(),actor));
			}
		}
	}
	++loadingProgress;
}

void DataManagerEx::createScene(fstream& loader)
{
	++loadingProgress;
}

void DataManagerEx::createItem(fstream& loader)
{
	++loadingProgress;
}

void DataManagerEx::createImage(fstream& loader)
{
	++loadingProgress;
}

