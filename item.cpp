#include "stdafx.h"
#include "item.h"

item::item(const std::string& name)
	: GameObject(name)
{
}

void item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void item::Init()
{
}

void item::Release()
{
}

void item::Reset()
{
}

void item::Update(float dt)
{
}

void item::Draw(sf::RenderWindow& window)
{
}