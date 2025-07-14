#include "stdafx.h"
#include "Platform.h"

std::unordered_map<TileType, const sf::Texture*> Platform:: texMap;

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

void Platform::SetType(TileType t)
{
	type = t;
	sprite.setTexture(*texMap[type]);
}

void Platform::Init()
{
	auto& mgr = TEXTURE_MGR;
	texMap[TileType::Ground] = &mgr.Get("img/Objectimg/map1img/platform1.png");
	//texMap[TileType::Floating] = &mgr.Get("tile_float");
	//texMap[TileType::Moving] = &mgr.Get("tile_move");
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