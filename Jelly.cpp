#include "stdafx.h"
#include "Jelly.h"

Jelly::Jelly(const std::string& name)
	: GameObject(name)
{
}

void Jelly::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	for (auto& s : sprites) s.setPosition(pos);
}

void Jelly::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	for (auto& spr : sprites) spr.setRotation(rot);
}

void Jelly::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	for (auto& spr : sprites) spr.setScale(s);
}

void Jelly::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	for (auto& spr : sprites) spr.setOrigin(o);
}

void Jelly::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
		for (auto& spr : sprites) Utils::SetOrigin(spr, preset);
}

void Jelly::Init()
{
	//spriteTexture.loadFromFile("graphics/jelly1.png");
	//sprite.setTexture(spriteTexture);
	//sprite.setTexture(TEXTURE_MGR.Get("graphics/jelly1.png"));

	texture1.loadFromFile("graphics/jelly1.png");
	texture2.loadFromFile("graphics/jelly2.png");
	texture3.loadFromFile("graphics/jelly3.png");
	texture4.loadFromFile("graphics/jelly4.png");
	jellySprite.setTexture(texture1);
	sprites.push_back(jellySprite);
	jellySprite.setTexture(texture2);
	sprites.push_back(jellySprite);
	jellySprite.setTexture(texture3);
	sprites.push_back(jellySprite);
	jellySprite.setTexture(texture4);
	sprites.push_back(jellySprite);
}

void Jelly::Release()
{
}

void Jelly::Reset()
{
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
	SetActive(true);
}

void Jelly::Reset(sf::Vector2f spawnPos)
{
	SetPosition({ spawnPos.x, spawnPos.y });
}

void Jelly::Update(float dt)
{
}

void Jelly::Draw(sf::RenderWindow& window)
{
	if (!GetActive()) return;
	window.draw(sprites[static_cast<size_t>(curType)]);
}

void Jelly::SetType(JellyType type)
{
	curType = type;
}