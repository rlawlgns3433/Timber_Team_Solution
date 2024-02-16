#include "pch.h"
#include "SceneDev1.h"
#include "ResourceManager.h"

SceneDev1::SceneDev1(SceneIDs id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{

}

void SceneDev1::Release()
{
}

void SceneDev1::Enter()
{

}

void SceneDev1::Exit()
{
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		SceneManager::Instance().ChangeScene(SceneIDs::SceneDev2);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Num1))
	{
		GameObject* findGameObject = FindGameObject("Message");
		findGameObject->SetActive(!findGameObject->GetActive());
	}
}
