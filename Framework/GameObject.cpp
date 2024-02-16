#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	: name(name)
{

}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(float x, float y)
{
}

void GameObject::SetOrigin(Origins preset)
{
	if (preset == Origins::CUSTOM);
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}

void GameObject::SetScale(const sf::Vector2f& scale)
{
}
