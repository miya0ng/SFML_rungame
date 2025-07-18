#include "stdafx.h"
#include "Coin.h"

Coin::Coin(const std::string& name)
	: GameObject(name)
{
}

void Coin::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	for (auto& s : sprites) s.setPosition(pos);
}

void Coin::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	for (auto& spr : sprites) spr.setRotation(rot);
}

void Coin::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	for (auto& spr : sprites) spr.setScale(s);
}

void Coin::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	for (auto& spr : sprites) spr.setOrigin(o);
}

void Coin::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
		for (auto& spr : sprites) Utils::SetOrigin(spr, preset);
}

void Coin::Init()
{
}

void Coin::Release()
{
}

void Coin::Reset()
{
	texture1.loadFromFile("graphics/silverCoin.png");
	texture2.loadFromFile("graphics/goldCoin.png");
	sprites[0].setTexture(texture1);
	sprites[1].setTexture(texture2);	
}

void Coin::Update(float dt)
{
}

void Coin::Draw(sf::RenderWindow& window)
{
	for (auto& spr : sprites)
		window.draw(sprites[static_cast<size_t>(curType)]);
}
void Coin::SetType(CoinType type)
{
	curType = type;
}