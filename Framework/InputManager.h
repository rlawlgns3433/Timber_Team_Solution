#pragma once
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <unordered_map>

// Ű���� �Է»� �ƴ϶� ���콺 �Է±��� �߰� �ʿ�

class InputManager
{
private:
	static std::unordered_map<sf::Keyboard::Key, bool> downKeyMap; // �̹� �����ӿ� down�� Ű���� ��Ƶδ� ����Ʈ, ���� Ű�� ����Ʈ�� ��� ��Ƽ� ó��
	static std::unordered_map<sf::Keyboard::Key, bool> upKeyMap;
	static std::unordered_map<sf::Keyboard::Key, bool> ingKeyMap;

	// �� ������ ������ keydown, keyup�� ������ �Ǿ�� �Ѵ�. �ϳ��� ������ ��������!
public:
	static void UpdateEvent(const sf::Event& event);
	static void Clear();
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	//static int EncryptKey(sf::Keyboard::Key key);
	//static sf::Keyboard::Key DecryptKey(int cipherText);
};