#include "pch.h"
#include "SceneTitle.h"
#include "ResourceManager.h"

SceneTitle::SceneTitle(SceneIDs id) : Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();
}

void SceneTitle::Release()
{
}

void SceneTitle::Enter()
{

}

void SceneTitle::Exit()
{
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		//SceneManager::Instance().ChangeScene(SceneIDs::SceneDev1);
	}
}
