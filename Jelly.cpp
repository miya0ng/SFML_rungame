#include "stdafx.h"
#include "Jelly.h"

Jelly::Jelly(const std::string& name)
	: GameObject(name)
{
}

void Jelly::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Jelly::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Jelly::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Jelly::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Jelly::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Jelly::Init()
{
	spriteTexture.loadFromFile("img/Objectimg/map1img/jelly2.png");
	sprite.setTexture(spriteTexture);
}

void Jelly::Release()
{
}

void Jelly::Reset()
{
}

void Jelly::Update(float dt)
{
}

void Jelly::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
