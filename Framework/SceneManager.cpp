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
	TEXTURE_MANAGER.Load(backgroundId);
	TEXTURE_MANAGER.Load(cloudId);
	TEXTURE_MANAGER.Load(beeId);
	TEXTURE_MANAGER.Load(treeId);
	TEXTURE_MANAGER.Load(branchId);
	TEXTURE_MANAGER.Load(logId);
	TEXTURE_MANAGER.Load(playerId);
	TEXTURE_MANAGER.Load(player2Id);
	TEXTURE_MANAGER.Load(ripId);
	TEXTURE_MANAGER.Load(axeId);

	// Font
	FONT_MANAGER.Load(fontId);

	// Sound, Music
	SOUND_MANAGER.Load(chopId);
	SOUND_MANAGER.Load(deathId);
	SOUND_MANAGER.Load(outOfTimeId);

	bgm.openFromFile(bgmId);
}

void SceneManager::PlayBGM()
{
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
