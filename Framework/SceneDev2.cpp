#include "pch.h"
#include "SceneDev2.h"
#include "ResourceManager.h"

SceneDev2::SceneDev2(SceneIDs id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();
}

void SceneDev2::Release()
{
}

void SceneDev2::Enter()
{

}

void SceneDev2::Exit()
{
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		SceneManager::Instance().ChangeScene(SceneIDs::SceneDev1);
	}
}
