#include "pch.h"
#include "SceneSelectMode.h"
#include "ResourceManager.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneSelectMode::SceneSelectMode(SceneIDs id) : Scene(id)
{
}

SceneSelectMode::~SceneSelectMode()
{
}

void SceneSelectMode::Init()
{
	ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();

	background = new SpriteGo("background");
	background->SetTexture(*textureManager.GetResource("graphics/background.png"));
	AddGameObject(background);

	pressNumber = new TextGo("pressNumber");
	pressNumber->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Press Num1 or Num2", 90, sf::Color::White);
	pressNumber->SetOrigin(Origins::MC);
	pressNumber->SetPosition(FRAMEWORK.GetWindowSize().x / 2, FRAMEWORK.GetWindowSize().y * 0.3f);
	AddGameObject(pressNumber);

	num1ForSinglePlay = new TextGo("num1ForSinglePlay");
	num1ForSinglePlay->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num1 For Single Play", 70, sf::Color::White);
	num1ForSinglePlay->SetOrigin(Origins::MC);
	num1ForSinglePlay->SetPosition(FRAMEWORK.GetWindowSize().x * (1.f / 4.f), FRAMEWORK.GetWindowSize().y * 0.6f);
	AddGameObject(num1ForSinglePlay);

	num2ForDuoPlay = new TextGo("num2ForDuoPlay");
	num2ForDuoPlay->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num2 For Duo Play", 70, sf::Color::White);
	num2ForDuoPlay->SetOrigin(Origins::MC);
	num2ForDuoPlay->SetPosition(FRAMEWORK.GetWindowSize().x * (3.f / 4.f), FRAMEWORK.GetWindowSize().y * 0.6f);
	AddGameObject(num2ForDuoPlay);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}

}

void SceneSelectMode::Release()
{
	Scene::Release();

	pressNumber = nullptr;
	num1ForSinglePlay = nullptr;
	num2ForDuoPlay = nullptr;

}

void SceneSelectMode::Enter()
{
	SCENEMANAGER.PlayBGM();
	Scene::Enter();
}

void SceneSelectMode::Exit()
{

}

void SceneSelectMode::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENEMANAGER.StopBGM();
		SCENEMANAGER.SetMode(SceneManager::Mod::SINGLE);
		SceneManager::Instance().ChangeScene(SceneIDs::SceneSelectCharacter);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENEMANAGER.StopBGM();
		SCENEMANAGER.SetMode(SceneManager::Mod::DUO);
		SceneManager::Instance().ChangeScene(SceneIDs::SceneSelectCharacter);
	}
}
