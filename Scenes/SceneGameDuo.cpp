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

	sf::Vector2f treePos1({ FRAMEWORK.GetWindowSize().x * 0.3f, 760});
	sf::Vector2f treePos2({ FRAMEWORK.GetWindowSize().x * 0.7f, 760});

	tree1 = new TreeGo("Tree1");
	tree2 = new TreeGo("Tree2");
	tree1->SetPosition(treePos1);
	tree2->SetPosition(treePos2);
	AddGameObject(tree1);
	AddGameObject(tree2);

	sf::Vector2f playerPos1({ treePos1.x + 150.f, 580.f });
	sf::Vector2f playerPos2({ treePos2.x + 150.f, 580.f });

	player1 = new PlayerGo("Player1");
	player2 = new PlayerGo("Player2");
	player1->SetPosition(playerPos1);
	player2->SetPosition(playerPos2);
	AddGameObject(player1);
	AddGameObject(player2);

	// UI
	sf::Vector2f TimebarPos1 = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f TimebarPos2 = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	TimebarPos1.x *= 0.3f;
	TimebarPos1.y *= 0.85f;
	TimebarPos2.x *= 0.7f;
	TimebarPos2.y *= 0.85f;

	timebar1 = new TimebarGo("Timebar1");
	timebar2 = new TimebarGo("Timebar2");
	timebar1->SetFillColor(sf::Color::Red);
	timebar2->SetFillColor(sf::Color::Red);
	timebar1->SetPosition(TimebarPos1);
	timebar2->SetPosition(TimebarPos2);
	timebar1->SetOrigin(Origins::MC);
	timebar2->SetOrigin(Origins::MC);

	AddGameObject(timebar1);
	AddGameObject(timebar2);


	uiScore1 = new UIScore("uiScore1");
	uiScore2 = new UIScore("uiScore2");
	uiScore1->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "uiScore1", 40, sf::Color::White);
	uiScore2->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "uiScore2", 40, sf::Color::White);
	uiScore1->SetOrigin(Origins::TL);
	uiScore2->SetOrigin(Origins::TL);
	uiScore1->SetPosition({ 0,0 });
	uiScore2->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,0});
	AddGameObject(uiScore1);
	AddGameObject(uiScore2);

	uiIntro = new TextGo("uiIntro");
	uiIntro->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "PRESS ENTER TO START!", 75, sf::Color::White);
	uiIntro->SetOrigin(Origins::MC);
	uiIntro->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGameObject(uiIntro);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SceneGameDuo::Release()
{
	Scene::Release();
}

void SceneGameDuo::Enter()
{
	Scene::Enter();
	SetStatus(Status::Awake);
}

void SceneGameDuo::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);

	uiScore1->SetOrigin(Origins::TL);
	uiScore1->SetPosition(0, 0);
	uiScore2->SetOrigin(Origins::TL);
	uiScore2->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,0 });

	for (auto& effectLog : useEffectList)
	{
		effectLog->SetActive(false);
		unuseEffectList.push_back(effectLog);
	}

	useEffectList.clear();
}

void SceneGameDuo::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneGameDuo::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGameDuo::Status::Game:
		UpdateGame(dt);
		break;
	case SceneGameDuo::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneGameDuo::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneGameDuo::UpdateAwake(float dt)
{
	player1->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.3f + 150.f, 580.f });
	player2->SetPosition({FRAMEWORK.GetWindowSize().x * 0.7f + 150.f, 580.f});

	SCENEMANAGER.PauseBGM();
	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		SCENEMANAGER.PlayBGM();
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENEMANAGER.ChangeScene(SceneIDs::SceneSelectCharacter);
		for (GameObject* obj : gameObjects)
		{
			obj->Reset();
		}
	}

	switch (SCENEMANAGER.GetPlayerOneSelect())
	{
	case 1:
		player1->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
		break;
	case 2:
		player1->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player2.png"));
		break;
	}

	switch (SCENEMANAGER.GetPlayerTwoSelect())
	{
	case 1:
		player2->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
		break;
	case 2:
		player2->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player2.png"));
		break;
	}
}

void SceneGameDuo::UpdateGame(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		SCENEMANAGER.PauseBGM();
	}
	if (InputManager::GetKeyDown(sf::Keyboard::LControl))
	{
		timebar1->AddTime(50.f);

		if (timebar1->GetCurrentRectSize().x >= timebar1->GetRectSize().x)
		{
			timebar1->SetRectSize(timebar1->GetRectSize());
		}
	}
	
	/////////////////////////////player1/////////////////////////////////////
	if (InputManager::GetKeyDown(sf::Keyboard::A) && !(int)player1->IsDead())
	{
		timebar1->AddTime(50.f);
		if (timebar1->GetCurrentRectSize().x >= timebar1->GetRectSize().x)
		{
			timebar1->SetRectSize(timebar1->GetRectSize());
		}
		tree1->Chop(Sides::LEFT);
		PlayEffectLog(Sides::LEFT, tree1);
		player1->UpdatePlayerSide(Sides::LEFT);
		player1->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.3f - 150.f, 580.f });
		uiScore1->AddScore(10.f);
		player1->SetAxeActive(true);

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/chop.wav"));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::A) && !(int)player1->IsDead())
	{
		player1->SetAxeActive(false);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::D) && !(int)player1->IsDead())
	{
		timebar1->AddTime(50.f);
		if (timebar1->GetCurrentRectSize().x >= timebar1->GetRectSize().x)
		{
			timebar1->SetRectSize(timebar1->GetRectSize());
		}
		tree1->Chop(Sides::RIGHT);
		PlayEffectLog(Sides::RIGHT, tree1);
		player1->UpdatePlayerSide(Sides::RIGHT);
		player1->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.3f + 150.f, 580.f });
		uiScore1->AddScore(10.f);
		player1->SetAxeActive(true);

		sound.resetBuffer();

		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/chop.wav"));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::D) && !(int)player1->IsDead())
	{
		player1->SetAxeActive(false);
	}


	if (player1->GetPlayerSide() == tree1->GetFirstBranch() && !(int)player1->IsDead()) // player1 사망 상태 - collide with branch
	{
		player1->SetDead();
		uiScore1->SetPosition({ 1920.f / 3, 1080.f / 2 - 200 });
		player1->SetPosition({ player1->GetPosition().x, 630 });

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/death.wav"));
		sound.play();
	}
	if (timebar1->GetCurrentRectSize().x <= 0 && !(int)player1->IsDead())				// player1 사망 상태 - timeover
	{
		player1->SetDead();
		uiScore1->SetPosition({ 1920.f / 3, 1080.f / 2 - 200 });
		player1->SetPosition({ player1->GetPosition().x, 630 });

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/out_of_time.wav"));
		sound.play();
	}

	////////////////////////player2///////////////////////////////
	if (InputManager::GetKeyDown(sf::Keyboard::Left) && !(int)player2->IsDead())
	{
		timebar2->AddTime(50.f);
		if (timebar2->GetCurrentRectSize().x >= timebar2->GetRectSize().x)
		{
			timebar2->SetRectSize(timebar2->GetRectSize());
		}
		tree2->Chop(Sides::LEFT);
		PlayEffectLog(Sides::LEFT, tree2);
		player2->UpdatePlayerSide(Sides::LEFT);
		player2->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.7f - 150.f, 580.f });
		uiScore2->AddScore(10.f);
		player2->SetAxeActive(true);

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/chop.wav"));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::Left) && !(int)player2->IsDead())
	{
		player2->SetAxeActive(false);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Right) && !(int)player2->IsDead())
	{
		timebar2->AddTime(50.f);
		if (timebar2->GetCurrentRectSize().x >= timebar2->GetRectSize().x)
		{
			timebar2->SetRectSize(timebar2->GetRectSize());
		}
		tree2->Chop(Sides::RIGHT);
		PlayEffectLog(Sides::RIGHT, tree2);
		player2->UpdatePlayerSide(Sides::RIGHT);
		player2->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.7f + 150.f, 580.f });
		uiScore2->AddScore(10.f);
		player2->SetAxeActive(true);

		sound.resetBuffer();

		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/chop.wav"));
		sound.play();
	}

	if (InputManager::GetKeyUp(sf::Keyboard::Right) && !(int)player2->IsDead())
	{
		player2->SetAxeActive(false);
	}

	if (player2->GetPlayerSide() == tree2->GetFirstBranch() && !(int)player2->IsDead()) // player2 사망 상태 - collide with branch
	{
		player2->SetDead();
		uiScore2->SetPosition({ 1920.f / 2, 1080.f / 2 - 200 });
		player2->SetPosition({ player2->GetPosition().x, 630 });

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/death.wav"));
		sound.play();
	}
	if (timebar2->GetCurrentRectSize().x <= 0 && !(int)player2->IsDead())				// player2 사망 상태 - timeover
	{
		player2->SetDead();
		uiScore2->SetPosition({ 1920.f / 2, 1080.f / 2 - 200 });
		player2->SetPosition({ player2->GetPosition().x, 630 });

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/out_of_time.wav"));
		sound.play();
	}

	if (player1->IsDead() == PlayerState::DEAD && player2->IsDead() == PlayerState::DEAD)
	{
		SetStatus(Status::GameOver);
		uiIntro->SetPosition({ 1920.f / 2, 1080.f * 0.2f });
		SCENEMANAGER.StopBGM();
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

void SceneGameDuo::UpdateGameOver(float dt)
{
	uiIntro->SetText("GAME OVER ^.^");

	if (uiScore1->GetUnsignedScore() > uiScore2->GetUnsignedScore())
	{
		uiIntro->SetText("Player1 Win!");
	}
	else if(uiScore1->GetUnsignedScore() < uiScore2->GetUnsignedScore())
	{
		uiIntro->SetText("Player2 Win!");
	}
	else
	{
		uiIntro->SetText("Draw");
	}

	uiIntro->SetPosition({ 1920.f / 2, 1080.f * 0.2f});

	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		Init();
		SetStatus(Status::Game);
		for (GameObject* obj : gameObjects)
		{
			obj->Reset();
		}

		switch (SCENEMANAGER.GetPlayerOneSelect())
		{
		case 1:
			player1->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
			break;
		case 2:
			player1->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player2.png"));
			break;
		}

		switch (SCENEMANAGER.GetPlayerTwoSelect())
		{
		case 1:
			player2->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
			break;
		case 2:
			player2->SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player2.png"));
			break;
		}

		uiScore1->SetPosition({ 0,0 });
		uiScore2->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,0 });

		for (auto& effectLog : useEffectList)
		{
			effectLog->SetActive(false);
			unuseEffectList.push_back(effectLog);
		}

		useEffectList.clear();

		SCENEMANAGER.PlayBGM();
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENEMANAGER.ChangeScene(SceneIDs::SceneSelectMode);
		for (GameObject* obj : gameObjects)
		{
			obj->Reset();
		}
	}
}

void SceneGameDuo::UpdatePause(float dt)
{
	if (InputManager::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
		SCENEMANAGER.PlayBGM();
	}
}

void SceneGameDuo::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGameDuo::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;

	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneGameDuo::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ENTER TO START!");
		break;
	case SceneGameDuo::Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		uiIntro->SetActive(false);
		break;
	case SceneGameDuo::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		break;
	case SceneGameDuo::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ESC TO RESUME!");
		break;
	}
}

void SceneGameDuo::PlayEffectLog(Sides side, const TreeGo* tree)
{
	EffectLog* effectLog = nullptr;

	if (unuseEffectList.empty())
	{
		effectLog = new EffectLog();
		effectLog->SetTexture("graphics/log.png");
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
