#pragma once
#include "Singleton.h"

// 클래스 전방 선언
// 해당 클래스가 있다는 것만 컴파일러에게 알림
class Scene; 


// 활성화 씬 관리
// 활성화 씬 변경
// 씬 생성 또는 삭제

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

protected:
	SceneManager(const SceneManager&)			 = delete;
	SceneManager(SceneManager&&)				 = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&)		 = delete;

	std::vector<Scene*> scenes;
	SceneIDs startScene = SceneIDs::SceneTitle;
	SceneIDs currentScene = startScene;

	sf::Music bgm;

	std::string backgroundId = "graphics/background.png";
	std::string cloudId = "graphics/cloud.png";
	std::string beeId = "graphics/bee.png";
	std::string treeId = "graphics/tree.png";
	std::string branchId = "graphics/branch.png";
	std::string logId = "graphics/log.png";
	std::string fontId = "fonts/KOMIKAP_.ttf";
	std::string playerId = "graphics/player.png";
	std::string player2Id = "graphics/player2.png";
	std::string ripId = "graphics/rip.png";
	std::string axeId = "graphics/axe.png";
	std::string chopId = "sound/chop.wav";
	std::string deathId = "sound/death.wav";
	std::string outOfTimeId = "sound/out_of_time.wav";
	std::string bgmId = "sound/kerning.mp3";

	int playeroneSelect = 0;
	int playertwoSelect = 0;

public:

	SceneManager() = default;
	virtual ~SceneManager();
	
	void Init(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의
	void Release(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	
	void ChangeScene(SceneIDs id);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	// TEST
	void SetPlayerOneSelect(int sel) { this->playeroneSelect = sel; }
	int GetPlayerOneSelect() { return this->playeroneSelect; }
	void SetPlayerTwoSelect(int sel) { this->playertwoSelect = sel; }
	int GetPlayerTwoSelect() { return this->playertwoSelect; }
	void LoadAllResources();
	void PlayBGM();
	void PauseBGM();
	void StopBGM();
};

#define SCENEMANAGER (Singleton<SceneManager>::Instance())