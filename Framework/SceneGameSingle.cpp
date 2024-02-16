#include "pch.h"
#include "SceneGameSingle.h"
#include "SpriteGo.h"
#include "BackgroundCloudGo.h"
#include "BackgroundBeeGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "TimebarGo.h"
#include "TreeGo.h"
#include "EffectLog.h"
#include "PlayerGo.h"

SceneGameSingle::SceneGameSingle(SceneIDs id) 
	: Scene(id)
{
}

SceneGameSingle::~SceneGameSingle()
{
}

void SceneGameSingle::Init()
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

	// TODO : ���� ���� �ÿ��� ����ǵ��� ���� �ʿ�!
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
	timebar->SetPosition(TimebarPos); // GameObject Ŭ���� �Լ� ȣ��� ���� �ʿ�
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

void SceneGameSingle::Release()
{
	Scene::Release();

	uiScore = nullptr;
	uiIntro = nullptr;
}

void SceneGameSingle::Enter()
{
	Scene::Enter();
	SetStatus(Status::Awake);
}

void SceneGameSingle::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGameSingle::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneGameSingle::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGameSingle::Status::Game:
		UpdateGame(dt);
	break;
	case SceneGameSingle::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneGameSingle::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneGameSingle::UpdateAwake(float dt)
{
	bgm.pause();
	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		bgm.play();
	}
} 

void SceneGameSingle::UpdateGame(float dt)
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

		sound.resetBuffer();
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

		sound.resetBuffer();

		sound.setBuffer(*SOUND_MANAGER.GetResource(chopId));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::Right))
	{
		player->SetAxeActive(false);
	}

	if (player->GetPlayerSide() == tree->GetFirstBranch()) // ��� ���� - collide with branch
	{
		player->SetDead();
		SetStatus(Status::GameOver);
		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource(deathId));
		sound.play();
		bgm.stop();
	}

	if (timebar->GetCurrentRectSize().x <= 0)				// ��� ���� - timeover
	{
		player->SetDead();
		SetStatus(Status::GameOver);
		sound.resetBuffer();
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
			it = useEffectList.erase(it);					// �������� ��ġ�� ���� ��ġ�� iterator�� ��ȯ
			unuseEffectList.push_back(effectGo);
		}
		else
		{
			++it;
		}
	}
}

void SceneGameSingle::UpdateGameOver(float dt)
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

void SceneGameSingle::UpdatePause(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
		bgm.play();
	}
}

void SceneGameSingle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGameSingle::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;

	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneGameSingle::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ENTER TO START!");
		break;
	case SceneGameSingle::Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		uiIntro->SetActive(false);
		break;
	case SceneGameSingle::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("GAME OVER ^.^");
		break;
	case SceneGameSingle::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ESC TO RESUME!");
		break;
	}
}

void SceneGameSingle::PlayEffectLog(Sides side)
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