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
}

void SceneSelectCharacter::Update(float dt)                              //1번 or 2번 캐릭터 선택 시 화면 전환.
{
	Scene::Update(dt);          
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::SINGLE)       //1인 모드          //수정하기  오호
	{
		if (InputManager::GetKeyDown(sf::Keyboard::Num1))                    //SelectMod에서 1인, 2인 어떤걸 선택했는지 어떻게 체크하지?
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(1);                             //잠와요 잠이와 일단 오류는 안나는데// 내일 집계약하러 갑니다아  
			SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle); //이렇게 하면 1인 모드로 밖에 못가는데 어쩌지???
		}
		if (InputManager::GetKeyDown(sf::Keyboard::Num2))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(2);
			SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle);
		}
	}
	else                              //2인 모드 2번 선택
	{
		
		if (InputManager::GetKeyDown(sf::Keyboard::Num1))                   
		{
			SCENEMANAGER.SetPlayerOneSelect(1);
			playerOneSelectCharacter = PlayerSelectCharacter::WoodCutter;
		}
		if (InputManager::GetKeyDown(sf::Keyboard::Num2))
		{
			SCENEMANAGER.SetPlayerOneSelect(2);
			playerOneSelectCharacter = PlayerSelectCharacter::YoungWoodCutter;
		}

		if (InputManager::GetKeyDown(sf::Keyboard::Num9)) 
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(1);
			playerTwoSelectCharacter = PlayerSelectCharacter::WoodCutter;
		}
		if (InputManager::GetKeyDown(sf::Keyboard::Num0))
		{
			SCENEMANAGER.StopBGM();
			SCENEMANAGER.SetPlayerOneSelect(2);
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
