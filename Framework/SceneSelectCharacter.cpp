#include "pch.h"
#include "SceneSelectCharacter.h"
#include "ResourceManager.h"

SceneSelectCharacter::SceneSelectCharacter(SceneIDs id) : Scene(id)
{
}

SceneSelectCharacter::~SceneSelectCharacter()
{
}

void SceneSelectCharacter::Init()
{

}

void SceneSelectCharacter::Release()
{
}

void SceneSelectCharacter::Enter()
{

}

void SceneSelectCharacter::Exit()
{
}

void SceneSelectCharacter::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		//SceneManager::Instance().ChangeScene(SceneIDs::SceneDev2);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Num1))
	{
		GameObject* findGameObject = FindGameObject("Message");
		findGameObject->SetActive(!findGameObject->GetActive());
	}
}
