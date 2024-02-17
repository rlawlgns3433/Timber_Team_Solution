#include "pch.h"
#include "SceneSelectCharacter.h"
#include "ResourceManager.h"
#include "BackgroundCloudGo.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneSelectCharacter::SceneSelectCharacter(SceneIDs id)
	: Scene(id)
{
}

SceneSelectCharacter::~SceneSelectCharacter()
{
}

void SceneSelectCharacter::Init()
{
	spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));
	AddGameObject(spriteGoBackground);

	SelectText = new TextGo("Select Character");
	SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Select Character", 100, sf::Color::White);
	SelectText->SetOrigin(Origins::MC);
	SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5, FRAMEWORK.GetWindowSize().y * 0.2);
	AddGameObject(SelectText);

	spritePlayer1 = new SpriteGo("player1");
	spritePlayer1->SetTexture(*textureManager.GetResource("graphics/player.png"));
	spritePlayer1->SetOrigin(Origins::BC);
	spritePlayer1->SetPosition({1920*0.3,1080*0.7});
	AddGameObject(spritePlayer1);

	spritePlayer2 = new SpriteGo("player2");                                     
	spritePlayer2->SetTexture(*textureManager.GetResource("graphics/player2.png"));
	spritePlayer2->SetOrigin(Origins::BC);
	spritePlayer2->SetPosition({ 1920 * 0.7,1080 * 0.7 });
	AddGameObject(spritePlayer2);

	SelectText = new TextGo("Num1 Character");
	SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num1 : Old WoodCutter", 30, sf::Color::Black);
	SelectText->SetOrigin(Origins::MC);
	SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.3, FRAMEWORK.GetWindowSize().y * 0.8 - 100);
	AddGameObject(SelectText);

	SelectText = new TextGo("Num2 Character");
	SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num2 : young WoodCutter", 30, sf::Color::Black);
	SelectText->SetOrigin(Origins::MC);
	SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.7, FRAMEWORK.GetWindowSize().y * 0.8 - 100);
	AddGameObject(SelectText);
}

void SceneSelectCharacter::Release()
{
	Scene::Release();
}

void SceneSelectCharacter::Enter()
{
	SCENEMANAGER.PlayBGM();
	Scene::Enter();
}

void SceneSelectCharacter::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
	spritePlayer1->SetScale({1.f, 1.f});
	spritePlayer2->SetScale({1.f, 1.f});
	playerOneSelectCharacter = PlayerSelectCharacter::None;
	playerTwoSelectCharacter = PlayerSelectCharacter::None;
}

void SceneSelectCharacter::Update(float dt)                              //1번 or 2번 캐릭터 선택 시 화면 전환.
{
	Scene::Update(dt);          
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::SINGLE)             //1인 모드         
	{
		if (InputManager::GetKeyDown(sf::Keyboard::Num1))                    
		{
			spritePlayer1->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num1))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(1);
			SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle);
		}

		if (InputManager::GetKeyDown(sf::Keyboard::Num2))
		{
			spritePlayer2->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num2))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(2);
			SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle);
		}
		
	}
	else                                                                 //2인 모드 2번 선택
	{
		SelectText = new TextGo("Num1 Character");
		SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num9 : Old WoodCutter", 30, sf::Color::Black);
		SelectText->SetOrigin(Origins::MC);
		SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.3, FRAMEWORK.GetWindowSize().y * 0.8);
		AddGameObject(SelectText);

		SelectText = new TextGo("Num2 Character");
		SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num0 : young WoodCutter", 30, sf::Color::Black);
		SelectText->SetOrigin(Origins::MC);
		SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.7, FRAMEWORK.GetWindowSize().y * 0.8);
		AddGameObject(SelectText);

		if (InputManager::GetKeyDown(sf::Keyboard::Num1))
		{
			spritePlayer1->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyDown(sf::Keyboard::Num2))
		{
			spritePlayer2->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num1))
		{
			spritePlayer1->SetScale({ 1.f, 1.f });
			SCENEMANAGER.SetPlayerOneSelect(1);
			playerOneSelectCharacter = PlayerSelectCharacter::WoodCutter;
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num2))
		{
			spritePlayer2->SetScale({ 1.f, 1.f });
			SCENEMANAGER.SetPlayerOneSelect(2);
			playerOneSelectCharacter = PlayerSelectCharacter::YoungWoodCutter;
		}

		if (InputManager::GetKeyDown(sf::Keyboard::Num9))
		{
			spritePlayer1->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyDown(sf::Keyboard::Num0))
		{
			spritePlayer2->SetScale({ 1.5f, 1.5f });
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num9))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerTwoSelect(1);
			playerTwoSelectCharacter = PlayerSelectCharacter::WoodCutter;
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Num0))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerTwoSelect(2);
			playerTwoSelectCharacter = PlayerSelectCharacter::YoungWoodCutter;
		}

		// 둘 다 선택된 경우 씬 전환
		if (playerOneSelectCharacter != PlayerSelectCharacter::None
			&& playerTwoSelectCharacter != PlayerSelectCharacter::None)
		{
			SCENEMANAGER.StopBGM();
			SceneManager::Instance().ChangeScene(SceneIDs::SceneGameDuo);
		}

	}
	
}
