#pragma once
#include "GameObject.h"
#include "TextGo.h"

class UiHud :
	public GameObject
{
protected:
	std::vector<sf::Text> texts;
	std::vector<sf::Vector2f> textPos;
	std::vector<sf::String> textString;
	std::vector<sf::RectangleShape> HpBars;
	sf::Vector2f hpBarSize;
	sf::Vector2f hpBarPos;
	std::string fontId;
	sf::Font font;
	sf::Text scoreText;
	sf::Text coinText;
	std::vector<sf::Vector2f> scorePos;
	std::vector<sf::String> scoreString;

	sf::Sprite hpBarSprite;
	sf::Sprite hpBarBG;
	sf::Sprite slideButton;
	sf::Sprite jumpButton;
	sf::Sprite jellyScoreIcon;
	sf::Sprite coinScoreIcon;
	sf::IntRect fullRect;
	sf::RectangleShape bgRect;
	sf::Texture* barFillTex{ nullptr };

	float scoreGuage = 0.f;
	int hp;
	int jellyScore = 0;
	int coinScore = 0;
	bool isShowMessage;
	bool isShowScore;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetCharacterSize(int size);
	void AddFontId(const sf::String id);
	void AddMessage(const sf::String Message);

	void SetScoreText(int s);
	void SetCoinText(int s);
	void SetHpRatio(float r);
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
