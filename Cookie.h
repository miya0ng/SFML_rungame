#pragma once
#include "GameObject.h"

class SpriteGo;

class Cookie :
	public GameObject
{
protected:
	sf::Sprite cookieOrigin;
	SpriteGo* cookiePtr;
	sf::Texture cookieTexture;
	std::string texId;

	sf::Vector2f velocity = { 0.f,0.f };
	sf::Vector2f position = { 0.f,0.f };

	float gravity = 0.f;

	float speed;

public:
	Cookie(const std::string& fontId = "", const std::string& name = "");
	virtual ~Cookie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::Vector2f GetPosition() { return position; }
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

