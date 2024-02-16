#include "pch.h"
#include "SceneTitle.h"
#include "ResourceManager.h"
#include "BackgroundCloudGo.h"


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

	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));
	AddGameObject(spriteGoBackground);
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
