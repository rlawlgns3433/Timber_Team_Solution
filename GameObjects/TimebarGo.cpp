#include "pch.h"
#include "TimebarGo.h"

TimebarGo::TimebarGo(const std::string& name)
	: GameObject(name)
{
	rectCurrentSize = rectSize;
	rectShape.setSize(rectCurrentSize);
	timebarSpeed = -rectSize.x / timebarDuration;
}

void TimebarGo::Update(float dt)
{
	rectCurrentSize.x += timebarSpeed * dt;
	if (rectCurrentSize.x > 0)
	{
		SetRectSize(rectCurrentSize);
	}
	else SetRectSize(EMPTY); // GameOver;
}

void TimebarGo::Reset()
{
	rectCurrentSize = rectSize;
	SetRectSize(rectCurrentSize);
}

void TimebarGo::Draw(sf::RenderWindow& window)
{
	window.draw(rectShape);
}

void TimebarGo::SetRectSize(const sf::Vector2f& size)
{
	this->rectCurrentSize = size;
	rectShape.setSize(size);
}

void TimebarGo::SetFillColor(const sf::Color& color)
{
	rectShape.setFillColor(color);
}

void TimebarGo::SetPosition(const sf::Vector2f& pos)
{
	rectShape.setPosition(pos);
}

void TimebarGo::SetOrigin(Origins preset)
{

	if (preset == Origins::CUSTOM)
	{
		preset == Origins::TL;
	}

	originPreset = preset;
	Utils::SetOrigin(rectShape, originPreset);
}

void TimebarGo::AddTime(float size)
{
	this->rectCurrentSize.x += size;
	rectShape.setSize(this->rectCurrentSize);
}
