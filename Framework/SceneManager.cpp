#include "pch.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneSelectCharacter.h"
#include "SceneSelectMode.h"
#include "SceneGameSingle.h"

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
	Release();

	scenes.push_back(new SceneTitle(SceneIDs::SceneTitle));
	scenes.push_back(new SceneSelectCharacter(SceneIDs::SceneSelectCharacter));
	scenes.push_back(new SceneSelectMode(SceneIDs::SceneSelectMode));
	scenes.push_back(new SceneGameSingle(SceneIDs::SceneGameSingle));
	
	for (auto scene : scenes)
	{
		scene->Init();
	}

	SCENEMANAGER.SetPlayerOneSelect(1);

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneManager::Release()
{
	for (auto scene : scenes)
	{
		scene->Release(); // �� ��� ������ �Ҵ� ����
		delete scene; // �� ����
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
