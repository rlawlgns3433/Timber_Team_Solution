#pragma once
#include "Scene.h"

class UIScore;
class TextGo;
class TimebarGo;
class TreeGo;
class EffectLog;
class PlayerGo;

class SceneGameDuo : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected :
	SceneGameDuo(const SceneGameDuo&)				 = delete;
	SceneGameDuo(SceneGameDuo&&)					 = delete;
	SceneGameDuo& operator=(const SceneGameDuo&)	 = delete;
	SceneGameDuo& operator=(SceneGameDuo&&)		 = delete;

public :

	UIScore* uiScore = nullptr;
	TextGo* uiIntro = nullptr;
	TimebarGo* timebar = nullptr;
	Status currentStatus = Status::Awake;
	TreeGo* tree = nullptr;
	PlayerGo* player = nullptr;

	sf::Sound sound;

	std::list<EffectLog*> useEffectList;
	std::list<EffectLog*> unuseEffectList;

public:
	SceneGameDuo(SceneIDs id);
	virtual ~SceneGameDuo();

	// Scene을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt);
	//void UpdateAwake(float dt);
	//void UpdateGame(float dt);
	//void UpdateGameOver(float dt);
	//void UpdatePause(float dt);
	//void Draw(sf::RenderWindow& window);

	//void SetStatus(Status newStatus);

	//void PlayEffectLog(Sides side);
};