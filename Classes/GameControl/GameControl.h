#pragma once
#include "cocos2d.h"
#include <tuple>
#include <vector>
#include <mutex>
#include "../script/ScriptManager.h"

class GameControl:
	public cocos2d::Node
{
public:
#define GAMESTART 100000000
	typedef struct { std::string name; Node* node; } message;
	static GameControl* getInstance();
	void gameLoop();
	void loadConfig();
	int randomActor();
	int getMaxSaveFile();
	void startGame();
	void advanceProgress();
	float getTextSpeed();

	void postNotification(std::string name, Node* node);

private:
	static GameControl* ptr;
	std::vector<int> activeActor;
	std::vector<message> notifications;
	float textSpeed;
	GameControl();
	GameControl(GameControl & gc) = default;

	void update(float delta) override;
	void updateProgress(float);

	int progress;
	int progressExpect;

	bool gameStarted;
};

