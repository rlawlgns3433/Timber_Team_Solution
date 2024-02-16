#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "BackgroundCloudGo.h"
#include "BackgroundBeeGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "TimebarGo.h"
#include "TreeGo.h"
#include "EffectLog.h"
#include "PlayerGo.h"

SceneGame::SceneGame(SceneIDs id) 
	: Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	// Texture
	textureManager.Load(backgroundId);
	textureManager.Load(cloudId);
	textureManager.Load(beeId);
	textureManager.Load(treeId);
	textureManager.Load(branchId);
	textureManager.Load(logId);
	textureManager.Load(playerId);
	textureManager.Load(ripId);
	textureManager.Load(axeId);

	// Font
	fontManager.Load(fontId);

	// Sound, Music
	soundManager.Load(chopId);
	soundManager.Load(deathId);
	soundManager.Load(outOfTimeId);

	// TODO : 게임 진행 시에만 재생되도록 변경 필요!
	bgm.openFromFile(bgmId);
	bgm.play();

	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource(backgroundId));
	AddGameObject(spriteGoBackground);

	sf::FloatRect cloudMovingBounds({ -200.f, 0 }, { 1920.f + 400, 600.f });
	sf::FloatRect beeMovingBounds({ 0.f, 540.f }, { 1920.f, 1080.f });

	for (int i = 1; i <= 3; ++i) {
		BackgroundCloudGo* backgroundGoCloud = new BackgroundCloudGo("Cloud" + std::to_string(i));
		backgroundGoCloud->SetTexture(*textureManager.GetResource(cloudId));
		backgroundGoCloud->SetOrigin(Origins::MC);
		backgroundGoCloud->SetPosition({ 0.f, 1080.f / 2 });
		backgroundGoCloud->SetBounds(cloudMovingBounds);
		AddGameObject(backgroundGoCloud);
	}

	sf::Vector2f treePos({ 960, 800 });

	tree = new TreeGo("Tree");
	tree->SetPosition(treePos);
	AddGameObject(tree);

	player = new PlayerGo("Player");
	AddGameObject(player);


	BackgroundBeeGo* backgroundGoBee = new BackgroundBeeGo("Bee");
	backgroundGoBee->SetTexture(*textureManager.GetResource(beeId));
	backgroundGoBee->SetOrigin(Origins::MC);
	backgroundGoBee->SetPosition({ 1920.f / 2, 800.f });
	backgroundGoBee->SetBounds(beeMovingBounds);
	AddGameObject(backgroundGoBee);



	// UI
	sf::Vector2f TimebarPos = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	TimebarPos.x *= 0.5f;
	TimebarPos.y *= 0.85f;

	timebar = new TimebarGo("Timebar");
	timebar->SetFillColor(sf::Color::Red);
	timebar->SetPosition(TimebarPos); // GameObject 클래스 함수 호출로 변경 필요
	timebar->SetOrigin(Origins::MC);

	AddGameObject(timebar);


	uiScore = new UIScore("uiScore");
	uiScore->Set(*fontManager.GetResource(fontId), "uiScore", 40, sf::Color::White);
	uiScore->SetOrigin(Origins::TL);
	uiScore->SetPosition({ 0,0 });
	AddGameObject(uiScore);

	uiIntro = new TextGo("uiIntro");
	uiIntro->Set(*fontManager.GetResource(fontId), "PRESS ENTER TO START!", 75, sf::Color::White);
	uiIntro->SetOrigin(Origins::MC);
	uiIntro->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGameObject(uiIntro);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SceneGame::Release()
{
	Scene::Release();

	uiScore = nullptr;
	uiIntro = nullptr;
}

void SceneGame::Enter()
{
	Scene::Enter();
	SetStatus(Status::Awake);
}

void SceneGame::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGame::Status::Game:
		UpdateGame(dt);
	break;
	case SceneGame::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneGame::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	bgm.pause();
	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		bgm.play();
	}
} 

void SceneGame::UpdateGame(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		bgm.pause();
	}
	if (InputManager::GetKeyDown(sf::Keyboard::LControl))
	{
		timebar->AddTime(50.f);

		if (timebar->GetCurrentRectSize().x >= timebar->GetRectSize().x)
		{
			timebar->SetRectSize(timebar->GetRectSize());
		}
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Left))
	{
		tree->Chop(Sides::LEFT);
		PlayEffectLog(Sides::LEFT);
		player->UpdatePlayerSide(Sides::LEFT);
		uiScore->AddScore(10.f);
		player->SetAxeActive(true);

		sound.setBuffer(*SOUND_MANAGER.GetResource(chopId));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::Left))
	{
		player->SetAxeActive(false);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Right))
	{
		tree->Chop(Sides::RIGHT);
		PlayEffectLog(Sides::RIGHT);
		player->UpdatePlayerSide(Sides::RIGHT);
		uiScore->AddScore(10.f);
		player->SetAxeActive(true);

		sound.setBuffer(*SOUND_MANAGER.GetResource(chopId));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::Right))
	{
		player->SetAxeActive(false);
	}

	if (player->GetPlayerSide() == tree->GetFirstBranch()) // 사망 상태 - collide with branch
	{
		player->SetDead();
		SetStatus(Status::GameOver);

		sound.setBuffer(*SOUND_MANAGER.GetResource(deathId));
		sound.play();
		bgm.stop();
	}

	if (timebar->GetCurrentRectSize().x <= 0)				// 사망 상태 - timeover
	{
		player->SetDead();
		SetStatus(Status::GameOver);

		sound.setBuffer(*SOUND_MANAGER.GetResource(outOfTimeId));
		sound.play();
		bgm.stop();
	}

	auto it = useEffectList.begin();
	while (it != useEffectList.end())
	{
		auto effectGo = *it;

		if (!effectGo->GetActive())
		{
			RemoveGameObject(effectGo);
			it = useEffectList.erase(it);					// 지워지는 위치의 다음 위치의 iterator가 반환
			unuseEffectList.push_back(effectGo);
		}
		else
		{
			++it;
		}
	}
}

void SceneGame::UpdateGameOver(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		for (GameObject* obj : gameObjects)
		{
			obj->Reset();
		}
		bgm.play();
	}
}

void SceneGame::UpdatePause(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
		bgm.play();
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;

	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ENTER TO START!");
		break;
	case SceneGame::Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		uiIntro->SetActive(false);
		break;
	case SceneGame::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("GAME OVER ^.^");
		break;
	case SceneGame::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ESC TO RESUME!");
		break;
	}
}

void SceneGame::PlayEffectLog(Sides side)
{
	EffectLog* effectLog = nullptr;

	if (unuseEffectList.empty())
	{
		effectLog = new EffectLog();
		effectLog->SetTexture(logId);
		effectLog->SetOrigin(Origins::BC);
		effectLog->Init();
	}
	else
	{
		effectLog = unuseEffectList.front();
		unuseEffectList.pop_front();
	}

	effectLog->SetActive(true);
	effectLog->Reset();
	effectLog->SetPosition({ tree->GetPosition() });

	sf::Vector2f velocity({ 700.f, -300.f });

	if (side == Sides::RIGHT)
	{
		velocity.x *= -1.f;
	}
	effectLog->Fire(velocity);

	useEffectList.push_back(effectLog);
	AddGameObject(effectLog);
}