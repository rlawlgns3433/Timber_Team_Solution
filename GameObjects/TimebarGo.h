#pragma once
#include "GameObject.h"
class TimebarGo : public GameObject
{
protected:
	TimebarGo(const TimebarGo& ref)				= delete;
	TimebarGo(TimebarGo&& ref)					= delete;
	TimebarGo& operator=(const TimebarGo& ref)  = delete;
	TimebarGo& operator=(TimebarGo&& ref)		= delete;



	sf::RectangleShape rectShape;
	sf::Vector2f rectSize = sf::Vector2f(400.f, 80.f);
	sf::Vector2f rectCurrentSize;
	sf::Vector2f EMPTY = sf::Vector2f({ 0.f,0.f });

	float timebarDuration = 3.f;
	float timebarSpeed;

public:
	TimebarGo(const std::string& name = "");
	virtual ~TimebarGo() = default;

	void Update(float dt)				override;
	void Reset()						override;
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetRectSize() const { return this->rectSize; }
	sf::Vector2f GetCurrentRectSize() const { return this->rectCurrentSize; }
	sf::RectangleShape& GetRect() { return this->rectShape; }
	void SetRectSize(const sf::Vector2f& size);
	void SetFillColor(const sf::Color& color);
	void SetPosition(const sf::Vector2f& pos);
	void SetOrigin(Origins preset);

	void AddTime(float size);
};