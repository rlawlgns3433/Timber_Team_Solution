#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIDs id) : id(id), textureManager(ResourceManager<sf::Texture>::Instance()), fontManager(ResourceManager<sf::Font>::Instance()),
	soundManager(ResourceManager<sf::SoundBuffer>::Instance())
{
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}

	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto& obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (auto& obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->GetName() == name)
		{
			return gameObject;
		}
	}

	return nullptr;
}

std::list<GameObject*>& Scene::FindAllGameObjectwithName(const std::string& name)
{
	gameObjects.clear();

	for (auto gameObject : gameObjects)
	{
		if (gameObject->GetName() == name)
		{
			gameObjects.push_back(gameObject);
		}
	}

	return gameObjects;
}

bool Scene::FindAll(const std::string& name, std::list<GameObject*>& list)
{
	bool isFind = false;
	list.clear();
	for (auto gameObject : gameObjects)
	{
		if (gameObject->GetName() == name)
		{
			list.push_back(gameObject);
			isFind = true;
		}
	}
	return isFind;
}

GameObject* Scene::AddGameObject(GameObject* gameObject)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), gameObject) == gameObjects.end())
	{
		gameObjects.push_back(gameObject);
		return gameObject;
	}
	return nullptr;
}

GameObject* Scene::AddGameObject(const std::string& name)
{
	GameObject* gameObject = FindGameObject(name);
	if (std::find(gameObjects.begin(), gameObjects.end(), gameObject) == gameObjects.end())
	{
		gameObjects.push_back(gameObject);
		return gameObject;
	}
	return nullptr;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	gameObjects.remove(gameObject);
}

void Scene::RemoveGameObject(std::string name)
{
	gameObjects.remove(FindGameObject(name));
}
