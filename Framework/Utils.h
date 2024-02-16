#pragma once
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include <random>

class Utils
{
private:
	//static int p;
	//static int q;
	//static int n;
	//static int z;
	//static int e;
	//static int d;

public:
	// Random
	static float RandomValue(); // 0.0 ~ 1.0
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static sf::Vector2f GetRandomVector2(float start, float end);
	static float GetRandomAngle();

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	//static int GetGCD(int a, int b);
	//static int GetPrivateKeyExponent(int exponent, int z);
	//static int Encrypt(int message, int exponent, int n);
	//static int Decrypt(int cipherText, int exponent, int n);
	//static bool IsPrime(int number);
	//static int GenerateRandomPrime(int min = 2, int max = 200);
	//static int GetPublicKeyExponent(int exponent);
};