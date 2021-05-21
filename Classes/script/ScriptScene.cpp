#include "ScriptScene.h"
#include "..\scene\StartScene.h"
#include "..\scene\StoryScene.h"
#include "..\public\CLFunction.h"

using namespace std;
USING_NS_CC;

ScriptScene::ScriptScene() :pathFile("")
{
	functionList[300] = &ScriptScene::sceneSwitch;
	functionList[301] = &ScriptScene::sceneEffect;
	functionList[305] = &ScriptScene::sceneSwitch;
	loadFunction[300] = &ScriptScene::loadSceneSwitch;
	loadFunction[301] = &ScriptScene::loadSceneEffect;
	loadFunction[305] = &ScriptScene::loadSceneSwitch;
	sceneEffects[1] = &ScriptScene::createSnow;
	sceneEffects[2] = &ScriptScene::createRain;
}

void ScriptScene::setContents(map<string, string> contents)
{
	type = myType::turnNum(contents["type"]);
	main = contents["contents"];
	(this->*loadFunction[type])(contents);
}

int ScriptScene::start()
{
	int result = -1;
	result = (this->*functionList[type])();
	return result;
}

int ScriptScene::sceneSwitch()
{
	Scene* prev = Director::getInstance()->getRunningScene();
	Scene* scene = nullptr;
	if (prev != nullptr)
	{
		if (prev->getChildByName("Dialog") != nullptr)
		{
			prev->removeChildByName("Dialog");
			return -1;
		}
	}
	switch (type % 100)
	{
	case 0:
		scene = StoryScene::createScene(pathFile);
		break;
	case 5:
		break;
	default:
		break;
	}
	log("scene created");
	auto transition = TransitionFade::create(2.0f, scene, Color3B::BLACK);
	Director::getInstance()->replaceScene(transition);
	return 1;
}

int ScriptScene::sceneEffect()
{
	int result = -1;
	auto target = Director::getInstance()->getRunningScene();
	if (target != nullptr && target->getChildByName("backGround")!= nullptr)
	{
		for (auto it = weather.begin(); it != weather.end(); it++)
		{
			(this->*sceneEffects[*it])();
		}
	}
	result = 0;
	return result;
}

void ScriptScene::loadSceneSwitch(std::map<std::string, std::string> _data)
{
	pathFile = "img/background/" + _data["contents"] + ".png";
}

/*这里以后还可以再改进，把SceneEffect集中到Game Data数据库中去，而不用一条脚本一个天气数据*/

void ScriptScene::loadSceneEffect(std::map<std::string, std::string> _data)
{
	if (_data["contents"].find('雪') != string::npos)
		weather.push_back(1);
	if (_data["contents"].find('雨') != string::npos)
		weather.push_back(2);
}

void ScriptScene::createSnow()
{
		auto particle = ParticleSnow::create();
		particle->setTexture(TextureCache::sharedTextureCache()->addImage("particles/000.png"));
		particle->setDuration(ParticleSystem::DURATION_INFINITY);
		particle->setPositionY(Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height);
		auto target = Director::getInstance()->getRunningScene()->getChildByName("backGround");
		target->addChild(particle);
}

void ScriptScene::createRain()
{
	auto particle = ParticleRain::create();
	particle->setDuration(ParticleSystem::DURATION_INFINITY);
	particle->setPositionY(Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height*0.95);
	auto target = Director::getInstance()->getRunningScene()->getChildByName("backGround");
	target->addChild(particle);
}