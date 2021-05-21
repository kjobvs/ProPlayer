#include "ScriptAudio.h"
#include "audio/include/AudioEngine.h"

using namespace std;
USING_NS_CC;
using namespace experimental;

void ScriptAudio::setContents(map<string,string> contents)
{
	switch (type % 100)
	{
	case 0:
		filePath = "Audio/me/" + contents["contents"] + ".ogg";
		break;
	case 1:
		filePath = "Audio/bgm/" + contents["contents"] + ".mp3";
		break;
	default:
		filePath = "";
		break;
	}
	id = -1;
}

int ScriptAudio::getAuidoID()
{
	return id;
}

int ScriptAudio::start()
{
	switch (type % 100)
	{
	case 0:
		id = AudioEngine::play2d(filePath);
		break;
	case 1:
		id = AudioEngine::play2d(filePath);
		AudioEngine::setLoop(id, true);
		break;
	default:
		break;
	}
	return 0;
}

