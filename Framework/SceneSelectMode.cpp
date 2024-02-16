#include "pch.h"
#include "SceneSelectMode.h"
#include "ResourceManager.h"

SceneSelectMode::SceneSelectMode(SceneIDs id) : Scene(id)
{
}

SceneSelectMode::~SceneSelectMode()
{
}

void SceneSelectMode::Init()
{
	ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();
}

void SceneSelectMode::Release()
{
}

void SceneSelectMode::Enter()
{

}

void SceneSelectMode::Exit()
{
}

void SceneSelectMode::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		//SceneManager::Instance().ChangeScene(SceneIDs::SceneDev1);
	}
}
