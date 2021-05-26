#include "GameControl.h"
#include "../DataLoader/DataManagerEx.h"
#include "../public/CLFunction.h"
#include <thread>
using namespace std;
USING_NS_CC;

std::mutex global_mutex;
std::mutex script_mutex;

GameControl* GameControl::ptr = nullptr;

GameControl* GameControl::getInstance()
{
	if (ptr == nullptr)
	{
		ptr = new GameControl();
	}
	return ptr;
}

GameControl::GameControl():gameStarted(false)
{
	activeActor = { 10000000 ,10000001};
	textSpeed = 0.02f;
	Director::getInstance()->getScheduler()->scheduleSelector(CC_SCHEDULE_SELECTOR(GameControl::update), this, 0.9, false);
	Director::getInstance()->getScheduler()->scheduleSelector(CC_SCHEDULE_SELECTOR(GameControl::updateProgress), this, 0.2, false);
}

void GameControl::loadConfig()
{}

int GameControl::randomActor()
{
	return activeActor[myFunction::random(0, activeActor.size()-1)];
}

int GameControl::getMaxSaveFile()
{
	return 99;
}

float GameControl::getTextSpeed()
{
	return textSpeed;
}

void GameControl::startGame()
{
	if (!gameStarted)
	{
		gameStarted = true;
		progress = GAMESTART;
		progressExpect = GAMESTART+1;
		gameLoop();
	}
}

void GameControl::gameLoop()
{
	log((myType::turnString(progress) + ":" + myType::turnString(progressExpect)).c_str());
	auto script = ScriptManager::getInstance()->getScriptByTag(progress);
	int result = script->start();
	if (result == 1)
	{
		++progress;
	}
	else if (result == 0)
	{
		++progress;
		++progressExpect;
	}
}

void GameControl::advanceProgress()
{
	if (progress == progressExpect)
		++progressExpect;
	if (progress < progressExpect)
	{
		gameLoop();
	}
}

void GameControl::update(float delta)
{
	lock_guard<mutex> guard(global_mutex);

	for (auto it = notifications.begin(); it != notifications.end(); it++)
	{
		NotificationCenter::sharedNotificationCenter()->postNotification(it->name, it->node);
	}
	notifications.clear();
}

void GameControl::updateProgress(float)
{
	if (progress < progressExpect)
		gameLoop();
}

void GameControl::postNotification(string name, Node* node)
{
	lock_guard<mutex> guard(global_mutex);

	message msg;
	msg.name = name;
	if (node != NULL)
		msg.node = node;
	else
		msg.node = NULL;
	
	notifications.push_back(msg);
}