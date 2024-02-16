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
	sf::Music bgm;

	std::list<EffectLog*> useEffectList;
	std::list<EffectLog*> unuseEffectList;

	std::string backgroundId = "graphics/background.png";
	std::string cloudId = "graphics/cloud.png";
	std::string beeId = "graphics/bee.png";
	std::string treeId = "graphics/tree.png";
	std::string branchId = "graphics/branch.png";
	std::string logId = "graphics/log.png";
	std::string fontId = "fonts/KOMIKAP_.ttf";
	std::string playerId = "graphics/player.png";
	std::string ripId = "graphics/rip.png";
	std::string axeId = "graphics/axe.png";
	std::string chopId = "sound/chop.wav";
	std::string deathId = "sound/death.wav";
	std::string outOfTimeId = "sound/out_of_time.wav";
	std::string bgmId = "sound/kerning.mp3";

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