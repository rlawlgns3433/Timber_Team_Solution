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
	SceneIDs startScene = SceneIDs::SceneGame;
	SceneIDs currentScene = startScene;

public:

	SceneManager() = default;
	virtual ~SceneManager();
	
	void Init(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의
	void Release(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	
	void ChangeScene(SceneIDs id);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENEMANAGER (Singleton<SceneManager>::Instance())