#pragma once
#include "GameObject.h"

class SpriteGo : public GameObject
{
protected :
	sf::Sprite sprite;

	SpriteGo(const SpriteGo&)				= delete;
	SpriteGo(SpriteGo&&)					= delete;
	SpriteGo& operator=(const SpriteGo&)	= delete;
	SpriteGo& operator=(SpriteGo&&)			= delete;

public :
	SpriteGo(const std::string& name);
	void SetTexture(const sf::Texture& texture);
	void SetTexture(const std::string& textureId);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset)			  override;
	void SetOrigin(const sf::Vector2f& origin)override;

	void SetScale(const sf::Vector2f& scale)  override;
	void SetFlipX(bool flip)				  override;
	void SetFlipY(bool flip)				  override;

	void Draw(sf::RenderWindow& window);
};