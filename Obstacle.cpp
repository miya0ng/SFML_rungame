#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(const std::string& name)
	:GameObject(name)
{
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

