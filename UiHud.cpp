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

void UiHud::SetHpBar(int currentHp, int maxHp, const sf::Vector2f& pos)
{

}

void UiHud::Init()
{
	font.loadFromFile("fonts/DS-DIGIT.TTF");
}

void UiHud::Release()
{

}

void UiHud::Reset()
{

}

void UiHud::Update(float dt)
{
	texts[0].setString("score: " + std::to_string(hp));
}

void UiHud::Draw(sf::RenderWindow& window)
{
	for (auto e : texts)
	{
		window.draw(e);
	}
}