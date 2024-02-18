#include "pch.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneSelectCharacter.h"
#include "SceneSelectMode.h"
#include "SceneGameSingle.h"
#include "SceneGameDuo.h"

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
	Release();
	LoadAllResources();
	scenes.push_back(new SceneTitle(SceneIDs::SceneTitle));
	scenes.push_back(new SceneSelectMode(SceneIDs::SceneSelectMode));
	scenes.push_back(new SceneSelectCharacter(SceneIDs::SceneSelectCharacter));
	scenes.push_back(new SceneGameSingle(SceneIDs::SceneGameSingle));
	scenes.push_back(new SceneGameDuo(SceneIDs::SceneGameDuo));

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneManager::Release()
{
	for (auto scene : scenes)
	{
		scene->Release(); // 씬 모든 내용을 할당 해제
		delete scene; // 씬 삭제
	}
	scenes.clear();
}

void SceneManager::ChangeScene(SceneIDs id)
{
	scenes[(int)currentScene]->Exit();
	currentScene = id;
	scenes[(int)currentScene]->Enter();
}

void SceneManager::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
}

void SceneManager::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}

void SceneManager::SetMode(Mod mod)
{
	currentMode = mod;
}

void SceneManager::LoadAllResources()
{
	// Texture
	TEXTURE_MANAGER.Load("graphics/background.png");
	TEXTURE_MANAGER.Load("graphics/cloud.png");
	TEXTURE_MANAGER.Load("graphics/bee.png");
	TEXTURE_MANAGER.Load("graphics/tree.png");
	TEXTURE_MANAGER.Load("graphics/branch.png");
	TEXTURE_MANAGER.Load("graphics/log.png");
	TEXTURE_MANAGER.Load("graphics/player.png");
	TEXTURE_MANAGER.Load("graphics/player2.png");
	TEXTURE_MANAGER.Load("graphics/rip.png");
	TEXTURE_MANAGER.Load("graphics/axe.png");

	// Font
	FONT_MANAGER.Load("fonts/KOMIKAP_.ttf");

	// Sound, Music
	SOUND_MANAGER.Load("sound/chop.wav");
	SOUND_MANAGER.Load("sound/death.wav");
	SOUND_MANAGER.Load("sound/out_of_time.wav");

	bgm.openFromFile(bgmId);
}

void SceneManager::PlayBGM()
{
	bgm.setLoop(true);
	bgm.play();
}

void SceneManager::PauseBGM()
{
	bgm.pause();
}

void SceneManager::StopBGM()
{
	bgm.stop();
}
