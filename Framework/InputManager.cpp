#include "InputManager.h"
#include "pch.h"
#include <algorithm>

std::unordered_map<sf::Keyboard::Key, bool> InputManager::downKeyMap;
std::unordered_map<sf::Keyboard::Key, bool> InputManager::upKeyMap;
std::unordered_map<sf::Keyboard::Key, bool> InputManager::ingKeyMap;

void InputManager::UpdateEvent(const sf::Event& event)
{
	// 해당 키가 리스트에 없다면 눌린 첫 프레임
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		// ingList에 없는 경우가 필요하다.
		if (!GetKey(event.key.code))
		{
			//downKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
			//ingKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
			downKeyMap[event.key.code] = true;
			ingKeyMap[event.key.code] = true;
		}
		break;

	case sf::Event::KeyReleased:
		//ingKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = false;
		//upKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
		ingKeyMap[event.key.code] = false;
		upKeyMap[event.key.code] = true;
		break;

	default:
		break;
	}
}

void InputManager::Clear()
{
	downKeyMap.clear();
	upKeyMap.clear();
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	//return downKeyMap[(sf::Keyboard::Key)EncryptKey(key)];
	return downKeyMap[key];
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	//return upKeyMap[(sf::Keyboard::Key)EncryptKey(key)];
	return upKeyMap[key];

}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	//return ingKeyMap[(sf::Keyboard::Key)EncryptKey(key)];
	return ingKeyMap[key];
}





//int InputManager::EncryptKey(sf::Keyboard::Key key)
//{
//	int p = Utils::GenerateRandomPrime();
//	int q = Utils::GenerateRandomPrime();
//	int n = p * q;
//	int z = (p - 1) * (q - 1);
//	int e = Utils::GetPublicKeyExponent(z);
//	int d = Utils::GetPrivateKeyExponent(e, z);
//	return Utils::Encrypt((int)key, e, n);
//}
//
//sf::Keyboard::Key InputManager::DecryptKey(int cipherText)
//{
//	int p = Utils::GenerateRandomPrime();
//	int q = Utils::GenerateRandomPrime();
//	int n = p * q;
//	int z = (p - 1) * (q - 1);
//	int e = Utils::GetPublicKeyExponent(z);
//	int d = Utils::GetPrivateKeyExponent(e, z);
//	return (sf::Keyboard::Key)(Utils::Decrypt(cipherText, d, n));
//}
