#include "stdafx.h"
#include "Cookie.h"
#include "SpriteGo.h"

Cookie::Cookie(const std::string& texId, const std::string& name)
	: GameObject(name),texId(texId)
{
}

void Cookie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	cookieOrigin.setPosition(pos);
}

void Cookie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	cookieOrigin.setRotation(rot);
}

void Cookie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	cookieOrigin.setScale(s);
}

void Cookie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	cookieOrigin.setOrigin(o);
}

void Cookie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(cookieOrigin, preset);
	}
}

void Cookie::Init()
{
	texId = "img/cookieimg/cookie1/player_attack.png";
}

void Cookie::Release()
{
	
}

void Cookie::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
	cookieOrigin.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition({ 100.f, 35.f });
}

void Cookie::Update(float dt)
{
	/*velocity.y += gravity * dt;
	position += velocity * dt;

	SetPosition(position);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		 {
			position.x += speed * dt;
		}
	}*/
}

void Cookie::Draw(sf::RenderWindow& window)
{
	window.draw(cookieOrigin);
}