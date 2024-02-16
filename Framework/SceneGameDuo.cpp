#include "pch.h"
#include "SceneGameDuo.h"
#include "SpriteGo.h"
#include "BackgroundCloudGo.h"
#include "BackgroundBeeGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "TimebarGo.h"
#include "TreeGo.h"
#include "EffectLog.h"
#include "PlayerGo.h"

SceneGameDuo::SceneGameDuo(SceneIDs id)
	: Scene(id)
{
}

SceneGameDuo::~SceneGameDuo()
{
}

void SceneGameDuo::Init()
{
	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));
	AddGameObject(spriteGoBackground);

	sf::FloatRect cloudMovingBounds({ -200.f, 0 }, { 1920.f + 400, 600.f });

	for (int i = 1; i <= 3; ++i) {
		BackgroundCloudGo* backgroundGoCloud = new BackgroundCloudGo("Cloud" + std::to_string(i));
		backgroundGoCloud->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
		backgroundGoCloud->SetOrigin(Origins::MC);
		backgroundGoCloud->SetPosition({ 0.f, 1080.f / 2 });
		backgroundGoCloud->SetBounds(cloudMovingBounds);
		AddGameObject(backgroundGoCloud);
	}

	sf::Vector2f treePos({ 960, 800 });

	tree = new TreeGo("Tree");
	tree->SetPosition(treePos);
	AddGameObject(tree);
}

void SceneGameDuo::Release()
{
}

void SceneGameDuo::Enter()
{
}

void SceneGameDuo::Exit()
{
}

void SceneGameDuo::Update(float dt)
{
}
