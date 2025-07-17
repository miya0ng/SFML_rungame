#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(const std::string& name)
	:GameObject(name)
{
}

void Obstacle ::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	obstacle.setPosition(pos);
}

void Obstacle ::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	obstacle.setRotation(rot);
}

void Obstacle ::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	obstacle.setScale(s);
}

void Obstacle ::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	obstacle.setOrigin(o);
}

void Obstacle ::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(obstacle, preset);
	}
}

void Obstacle::Init()
{	
	texture.loadFromFile("graphics/corn.png");
	obstacle.setTexture(texture);
}

void Obstacle::Release()
{

}

void Obstacle::Reset()
{

}

void Obstacle::Update(float dt)
{
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	window.draw(obstacle);
}

