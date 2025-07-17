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
	hpBarTexture.loadFromFile("graphics/lifeBar.png");
	hpBarSprite.setTexture(hpBarTexture);
	jumpTexture.loadFromFile("graphics/jumpno.png");
	jumpButton.setTexture(jumpTexture);
	slideTexture.loadFromFile("graphics/slideno.png");
	slideButton.setTexture(slideTexture);

	font.loadFromFile("fonts/DS-DIGIT.TTF");
	sf::FloatRect bounds = scoreText.getLocalBounds();
	scoreText.setOrigin({ bounds.width / 2, 0});
	scoreText.setPosition({ FRAMEWORK.GetWindowBounds().width*0.5f-100.f, 40.f });
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setFont(font);

	hpBarSprite.setPosition({ FRAMEWORK.GetWindowBounds().width/2, 0.f });
	hpBarSprite.setOrigin({ hpBarSprite.getGlobalBounds().width / 2, 0.f });
	hpBarSprite.setScale(0.7f, 0.7f);
	slideButton.setPosition({ 0, FRAMEWORK.GetWindowBounds().height - 100.f });
	slideButton.setScale(0.8f, 0.8f);
	jumpButton.setPosition({ FRAMEWORK.GetWindowBounds().width- 120.f, FRAMEWORK.GetWindowBounds().height-100.f});
	jumpButton.setScale(0.8f, 0.8f);
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
	//window.setView(uiView);
	window.draw(scoreText);
	window.draw(hpBarSprite);
	window.draw(jumpButton);
	window.draw(slideButton);
	/*for (auto e : texts)
	{
		window.draw(e);
	}*/
}