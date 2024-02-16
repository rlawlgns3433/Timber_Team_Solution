#pragma once
#include "Singleton.h"

template <typename T>
class ResourceManager : public Singleton<ResourceManager<T>> // 템플릿 클래스
{
private:
	std::unordered_map<std::string, T*> resourceMap;
	friend class Singleton<ResourceManager<T>>;

public:
	ResourceManager(const ResourceManager& ref)				= delete;
	ResourceManager(ResourceManager&& ref)					= delete;
	ResourceManager& operator=(const ResourceManager& ref)	= delete;
	ResourceManager& operator=(ResourceManager&& ref)		= delete;

	static T Empty;
	ResourceManager() = default;
	virtual ~ResourceManager()
	{
		UnloadAll();
	}

	bool Load(const std::string& filePath) // 리소스 업로드
	{
		if(resourceMap.find(filePath) != resourceMap.end())
		{
			return false;
		}

		T* resource = new T();

		bool isSuccess = resource->loadFromFile(filePath);

		if (isSuccess)
		{
			resourceMap[filePath] = resource;
		}

		return isSuccess;
	}
	void UnloadAll()
	{
		for (const auto& pair : resourceMap) // pair는 타입이 pair이다.
		{
			delete pair.second; // 전체 동적 할당 받은 두 번째 요소를 할당 해제
		}

		resourceMap.clear(); // 해시 맵 내용 정리
	}
	bool Unload(const std::string& filePath) // 리소스 언로드
	{
		auto it = resourceMap.find(filePath);
		if (it == resourceMap.end())
		{
			return false;
		}
		
		delete it->second;
		resourceMap.erase(it);
		return true;
	}
	T* GetResource(const std::string& filePath) // 리소스 찾기
	{
		auto it = resourceMap.find(filePath);
		if (it == resourceMap.end())
		{
			return nullptr;
		}

		return it->second;
	}
	
};

template <typename T>
T ResourceManager<T>::Empty;  // 정적 변수 초기화

#define FONT_MANAGER (Singleton<ResourceManager<sf::Font>>::Instance())
#define TEXTURE_MANAGER (Singleton<ResourceManager<sf::Texture>>::Instance())
#define SOUND_MANAGER (Singleton<ResourceManager<sf::SoundBuffer>>::Instance())