#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	textPos.push_back(pos);
}

void UiHud::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
}

void UiHud::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
}

void UiHud::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	/*if (preset != Origins::Custom)
	{
		Utils::SetOrigin(gameObject, preset);
	}*/
}

void UiHud::SetCharacterSize(int size)
{
}

void UiHud::AddFontId(const sf::String fontId)
{
	if (!font.loadFromFile("fonts/DS-DIGIT.TTF"))
	{
		std::cout << "Failed to load files" << std::endl;
	}
}

void UiHud::AddMessage(const sf::String Message)
{
	textString.push_back(Message);
}

void UiHud::SetScoreText(int s)
{
	jellyScore = s;
}

void UiHud::SetHpBar(int currentHp, int maxHp, const sf::Vector2f& pos)
{
	
}

void UiHud::Init()
{
	font.loadFromFile("fonts/DS-DIGIT.TTF");
	scoreText.setPosition({ FRAMEWORK.GetWindowBounds().width*0.5f-100.f,30});
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setFont(font);
}

void UiHud::Release()
{

}

void UiHud::Reset()
{

}

void UiHud::Update(float dt)
{
	scoreText.setString("jelly: " + std::to_string(jellyScore));
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(scoreText);
	/*for (auto e : texts)
	{
		window.draw(e);
	}*/
}