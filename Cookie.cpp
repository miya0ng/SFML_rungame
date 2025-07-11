#include "stdafx.h"
#include "Cookie.h"

Cookie::Cookie(const std::string& name)
	: GameObject(name)
{
}

void Cookie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Cookie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Cookie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Cookie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Cookie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Cookie::Init()
{
}

void Cookie::Release()
{
}

void Cookie::Reset()
{
}

void Cookie::Update(float dt)
{
}

void Cookie::Draw(sf::RenderWindow& window)
{
}