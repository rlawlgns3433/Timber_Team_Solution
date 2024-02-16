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
	SceneIDs startScene = SceneIDs::SceneGameSingle;
	SceneIDs currentScene = startScene;

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
};

#define SCENEMANAGER (Singleton<SceneManager>::Instance())