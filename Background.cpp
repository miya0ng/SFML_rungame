#include "stdafx.h"
#include "Background.h"
#include "AniPlayer.h"

Background::Background()
{
		
}

void Background::Init()
{
	backgroundTexture.loadFromFile("img/Objectimg/map1img/bg1.png");
	background1.setTexture(backgroundTexture);
	background2.setTexture(backgroundTexture);
	backgroundWidth = backgroundTexture.getSize().x;
}

void Background::Enter()
{

}

void Background::Update(float dt)
{
	scrollOffset += dt * aniPlayer->GetSpeed();

	background1.setPosition(-scrollOffset, 0);
	background2.setPosition(-scrollOffset + backgroundWidth, 0);

	if (scrollOffset >= backgroundWidth)
	{
		scrollOffset -= backgroundWidth;
	}
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(background1);
	window.draw(background2);
}

void Background::Exit()
{

}
