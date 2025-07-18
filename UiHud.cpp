#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
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

void UiHud::SetCoinText(int c)
{
	coinScore = c;
}

void UiHud::SetHpRatio(float r)
{ 
	r = Utils::Clamp(r, 0.f, 1.f);
	sf::IntRect rect = fullRect;
	rect.width = static_cast<int>(fullRect.width * r);
	hpBarSprite.setTextureRect(rect);
}
void UiHud::Init()
{
	
}

void UiHud::Release()
{

}

void UiHud::Reset()
{
	slideButton.setTexture(TEXTURE_MGR.Get("graphics/slideno.png"));
	jumpButton.setTexture(TEXTURE_MGR.Get("graphics/jumpno.png"));
	jellyScoreIcon.setTexture(TEXTURE_MGR.Get("graphics/jelly1.png"));
	coinScoreIcon.setTexture(TEXTURE_MGR.Get("graphics/silverCoin.png"));
	hpBarSprite.setTexture(TEXTURE_MGR.Get("graphics/lifeBar.png"));
	
	scoreText.setFont(FONT_MGR.Get("fonts/CookieRun Bold.ttf"));
	coinText.setFont(FONT_MGR.Get("fonts/CookieRun Bold.ttf"));

	coinScoreIcon.setPosition({ 10.f, 60.f });
	coinScoreIcon.setScale(0.7f, 0.7f);

	sf::FloatRect coinBounds = coinText.getLocalBounds();
	coinText.setOrigin({ coinBounds.width / 2, 0 });
	coinText.setPosition({ coinScoreIcon.getPosition().x + 35.f, coinScoreIcon.getPosition().y });
	coinText.setCharacterSize(20);
	coinText.setOutlineThickness(2.f);
	coinText.setOutlineColor(sf::Color::Black);
	coinText.setFillColor(sf::Color::White);


	hpBarBG.setOrigin(FRAMEWORK.GetWindowBounds().width * 0.5f, 0.f);
	hpBarBG.setPosition(FRAMEWORK.GetWindowBounds().width * 0.5f, 0.f);
	hpBarSprite.setOrigin(hpBarSprite.getLocalBounds().width * 0.5f, 0.f);
	hpBarSprite.setPosition(FRAMEWORK.GetWindowBounds().width * 0.5f, 0.f);
	hpBarSprite.setScale(0.7f, 0.7f);
	fullRect = hpBarSprite.getTextureRect();

	sf::Vector2f barSize{ hpBarSprite.getGlobalBounds().width - 30.f,
						  hpBarSprite.getGlobalBounds().height*0.3f, };
	bgRect.setSize(barSize);
	bgRect.setOrigin(barSize.x * 0.5f, 0.f);
	bgRect.setPosition(hpBarSprite.getPosition().x, hpBarSprite.getPosition().y + 23.f);
	bgRect.setFillColor(sf::Color(0, 0, 0, 100));

	sf::FloatRect bounds = scoreText.getLocalBounds();
	scoreText.setOrigin({ bounds.width / 2, 0 });
	scoreText.setPosition({ FRAMEWORK.GetWindowBounds().width * 0.5f - 50.f, 40.f });
	scoreText.setCharacterSize(20);
	scoreText.setOutlineThickness(2.f);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setFillColor(sf::Color::White);
	jellyScoreIcon.setPosition({ scoreText.getPosition().x - jellyScoreIcon.getGlobalBounds().width, scoreText.getPosition().y});
	jellyScoreIcon.setScale(0.7f, 0.7f);


	slideButton.setPosition({ 10, FRAMEWORK.GetWindowBounds().height - 100.f });
	jumpButton.setPosition({ FRAMEWORK.GetWindowBounds().width - 140.f, FRAMEWORK.GetWindowBounds().height - 100.f });
}

void UiHud::Update(float dt)
{
	scoreText.setString(std::to_string(jellyScore));
	coinText.setString(std::to_string(coinScore));
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(scoreText);
	window.draw(coinText);
	window.draw(bgRect);
	window.draw(hpBarSprite);
	window.draw(jumpButton);
	window.draw(slideButton);
	window.draw(jellyScoreIcon);
	window.draw(coinScoreIcon);
	/*for (auto e : texts)
	{
		window.draw(e);
	}*/
}