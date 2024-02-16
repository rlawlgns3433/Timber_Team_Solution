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

	spritePlayer1 = new SpriteGo("plater1");
	spritePlayer1->SetTexture(*textureManager.GetResource("graphics/player.png"));
	spritePlayer1->SetOrigin(Origins::BC);
	spritePlayer1->SetPosition({1920*0.3,1080*0.7});
	AddGameObject(spritePlayer1);

	/*spritePlayer2 = new SpriteGo("plater2");                                     //아직 player2가 로드 안됨
	spritePlayer2->SetTexture(*textureManager.GetResource("graphics/player2.png"));
	spritePlayer2->SetOrigin(Origins::BC);
	spritePlayer2->SetPosition({ 1920 * 0.7,1080 * 0.5 });
	AddGameObject(spritePlayer2);*/

	SelectText = new TextGo("Num1 Character");
	SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num1 : Old WoodCutter", 30, sf::Color::Black);
	SelectText->SetOrigin(Origins::MC);
	SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.3, FRAMEWORK.GetWindowSize().y * 0.8 - 100);
	AddGameObject(SelectText);

	SelectText = new TextGo("Num2 Character");
	SelectText->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "Num2 : young WoodCutter", 30, sf::Color::Black);
	SelectText->SetOrigin(Origins::MC);
	SelectText->SetPosition(FRAMEWORK.GetWindowSize().x * 0.6, FRAMEWORK.GetWindowSize().y * 0.8 - 100);
	AddGameObject(SelectText);

	


}

void SceneSelectCharacter::Release()
{
	Scene::Release();
}

void SceneSelectCharacter::Enter()
{
	Scene::Enter();
}

void SceneSelectCharacter::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneSelectCharacter::Update(float dt)                              //1번 or 2번 캐릭터 선택 시 화면 전환.
{
	Scene::Update(dt);                                                  

	if (InputManager::GetKeyDown(sf::Keyboard::Num1))                    //SelectMod에서 1인, 2인 어떤걸 선택했는지 어떻게 체크하지?
	{
		SCENEMANAGER.SetPlayerOneSelect(1);                              //
		SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle); //이렇게 하면 1인 모드로 밖에 못가는데 어쩌지???
																		
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENEMANAGER.SetPlayerTwoSelect(1);
		SceneManager::Instance().ChangeScene(SceneIDs::SceneGameSingle);
	}
}
