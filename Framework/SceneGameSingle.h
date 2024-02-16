#pragma once
#include "Scene.h"

class UIScore;
class TextGo;
class TimebarGo;
class TreeGo;
class EffectLog;
class PlayerGo;

class SceneGameSingle : public Scene
{
public :
	// Scene의 상태
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	SceneGameSingle(const SceneGameSingle&)				 = delete;
	SceneGameSingle(SceneGameSingle&&)					 = delete;
	SceneGameSingle& operator=(const SceneGameSingle&)	 = delete;
	SceneGameSingle& operator=(SceneGameSingle&&)		 = delete;

	UIScore* uiScore = nullptr;
	TextGo* uiIntro = nullptr;
	TimebarGo* timebar = nullptr;
	Status currentStatus = Status::Awake;
	TreeGo* tree = nullptr;
	PlayerGo* player = nullptr;

	sf::Sound sound;

	std::list<EffectLog*> useEffectList;
	std::list<EffectLog*> unuseEffectList;

public :
	SceneGameSingle(SceneIDs id);
	virtual ~SceneGameSingle();
	
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window);

	void SetStatus(Status newStatus);

	void PlayEffectLog(Sides side);

};