#include "pch.h"
#include "BackgroundBeeGo.h"

BackgroundBeeGo::BackgroundBeeGo(const std::string& name)
	: BackgroundMovingGo(name)
{
}

void BackgroundBeeGo::Update(float dt)
{
	time += dt;
	position += direction * speed * dt;

	if (direction.x > 0.f) { sprite.setScale(-1.f, 1.f); }
	else if (direction.x < 0.f) { sprite.setScale(1.f, 1.f); }

	if (time > beeChangeTime)
	{
		ReDirection();
	}
	sprite.setPosition(position);
}

void BackgroundBeeGo::Reset()
{
	sprite.setPosition(960.f, 540.f);
}

void BackgroundBeeGo::ReDirection()
{
	float angle = Utils::GetRandomAngle();
	std::cout << angle << std::endl;

	rotation.rotate(angle);
	direction = rotation * direction;
	std::cout << direction.x << " : " << direction.y << std::endl;

	beeChangeTime = time + beeChangeDuration;
}
