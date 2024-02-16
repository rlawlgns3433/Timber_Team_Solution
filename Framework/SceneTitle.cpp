#include "pch.h"
#include "SceneTitle.h"
#include "ResourceManager.h"
#include "BackgroundCloudGo.h"
#include "SpriteGo.h"
#include "TextGo.h"


SceneTitle::SceneTitle(SceneIDs id)
	: Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	LoadAllResources();

	spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));
	AddGameObject(spriteGoBackground);

	//UI
	textTitle = new TextGo("textTitle");
	textTitle->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "CUNNING CITY ", 100, sf::Color::White);
	textTitle->SetOrigin(Origins::MC);
	textTitle->SetPosition(FRAMEWORK.GetWindowSize().x / 2, FRAMEWORK.GetWindowSize().y * 0.3f);
	AddGameObject(textTitle);

	textIntro = new TextGo("textIntro");
	textIntro->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "PRESS ENTER TO SELECT MODE ", 75, sf::Color::White);
	textIntro->SetOrigin(Origins::MC);
	textIntro->SetPosition(FRAMEWORK.GetWindowSize().x / 2, FRAMEWORK.GetWindowSize().y / 2);
	AddGameObject(textIntro);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SceneTitle::Release()
{
	Scene::Release();

	textIntro = nullptr;

}

void SceneTitle::Enter()
{
	Scene::Enter();

}

void SceneTitle::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	time += dt;

	BlinkIntro(0.7f);

	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneManager::Instance().ChangeScene(SceneIDs::SceneSelectMode);
	}
}

void SceneTitle::LoadAllResources()
{
	// Texture
	textureManager.Load("graphics/background.png");
	textureManager.Load("graphics/cloud.png");
	textureManager.Load("graphics/bee.png");
	textureManager.Load("graphics/tree.png");
	textureManager.Load("graphics/branch.png");
	textureManager.Load("graphics/log.png");
	textureManager.Load("graphics/player.png");
	textureManager.Load("graphics/rip.png");
	textureManager.Load("graphics/axe.png");

	// Font
	fontManager.Load("fonts/KOMIKAP_.ttf");

	// Sound, Music
	soundManager.Load("sound/chop.wav");
	soundManager.Load("sound/death.wav");
	soundManager.Load("sound/out_of_time.wav");
}

void SceneTitle::BlinkIntro(float blinkTime)
{
	this->blinkTime = blinkTime;

	if (time >= 0 && time < blinkTime)
	{
		textIntro->SetActive(true);
	}
	else if (time >= blinkTime && time < blinkTime * 2)
	{
		textIntro->SetActive(false);
	}
	else if (time >= blinkTime * 2)
	{
		time = 0.f;
	}
}
