#pragma once
#include "Singleton.h"

// Ŭ���� ���� ����
// �ش� Ŭ������ �ִٴ� �͸� �����Ϸ����� �˸�
class Scene; 


// Ȱ��ȭ �� ����
// Ȱ��ȭ �� ����
// �� ���� �Ǵ� ����

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
	
	void Init(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����
	void Release(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����

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