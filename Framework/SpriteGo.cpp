#include "pch.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& name)
	: GameObject(name)
{
}

void SpriteGo::SetTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void SpriteGo::SetTexture(const std::string& textureId)
{
	SetTexture(*ResourceManager<sf::Texture>::Instance().GetResource(textureId));
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;

	sprite.setPosition(this->position);
}

void SpriteGo::SetOrigin(Origins preset)
{

	if (preset == Origins::CUSTOM)
	{
		preset == Origins::TL;
	}

	originPreset = preset;
	Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& origin)
{
	originPreset = Origins::CUSTOM;
	this->origin = origin;
	sprite.setOrigin(this->origin);
}

void SpriteGo::SetScale(const sf::Vector2f& scale)
{
	sf::Vector2f spriteScale = this->scale = scale;

	if (isFlipX)
	{
		spriteScale.x = -spriteScale.x;
	}

	if (isFlipY)
	{
		spriteScale.y = -spriteScale.y;
	}

	sprite.setScale(spriteScale);
}

void SpriteGo::SetFlipX(bool flip)
{
	if (isFlipX == flip) return;
	isFlipX = flip;

	SetScale(scale);
}

void SpriteGo::SetFlipY(bool flip)
{
	if (isFlipY == flip) return;
	isFlipY = flip;

	SetScale(scale);
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
