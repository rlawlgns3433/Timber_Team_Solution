#include "pch.h"
#include "SceneManager.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneGame.h"

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
	Release();

	scenes.push_back(new SceneDev1(SceneIDs::SceneDev1));
	scenes.push_back(new SceneDev2(SceneIDs::SceneDev2));
	scenes.push_back(new SceneGame(SceneIDs::SceneGame));
	
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
