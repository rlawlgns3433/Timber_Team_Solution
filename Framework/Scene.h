#pragma once
#include <memory>
class GameObject;

class Scene
{
protected :
	Scene(const Scene&)				= delete;
	Scene(Scene&&)					= delete;
	Scene& operator=(const Scene&)  = delete;
	Scene& operator=(Scene&&)		= delete;

	SceneIDs id;
	std::unordered_map<size_t, std::vector<GameObject*>> gameObjectsMap;

	std::list<GameObject*> gameObjects; // 스마트 포인터로 변경 필요
	std::list<GameObject*> gameOBjectsActive; // 활성화 된 GameObjects
	std::list<GameObject*> gameOBjectsInActive; // 비활성화 된 GameObjects

	ResourceManager<sf::Texture>& textureManager;
	ResourceManager<sf::Font>& fontManager;
	ResourceManager<sf::SoundBuffer>& soundManager;

	// active, inactive 된 gameobjects를 다르게 관리하는 리스트 필요

public :
	Scene(SceneIDs id);
	virtual ~Scene() = default;

	virtual void Init() = 0; // Scene 최초 생성
	virtual void Release();

	virtual void Enter(); // Scene 입장 시
	virtual void Exit() = 0;
	
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual GameObject* FindGameObject(const std::string& name);
	virtual std::list<GameObject*>& FindAllGameObjectwithName(const std::string& name);
	virtual bool FindAll(const std::string& name, std::list<GameObject*>& list);
	virtual GameObject* AddGameObject(GameObject* gameObject);
	virtual GameObject* AddGameObject(const std::string& name);
	virtual void RemoveGameObject(GameObject* gameObject);
	virtual void RemoveGameObject(std::string name);
};