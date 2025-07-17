#include "stdafx.h"
#include "Platform.h"


Platform::Platform(const std::string& name)
	: GameObject(name)
{
}

void Platform::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Platform::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Platform::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Platform::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Platform::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Platform::Init()
{
	texture.loadFromFile("graphics/platform.png");
	sprite.setTexture(texture);
}

void Platform::Release()
{
}

void Platform::Reset()
{
}

void Platform::Update(float dt)
{

}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}