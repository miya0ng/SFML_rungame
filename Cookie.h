#pragma once
#include "GameObject.h"

class SpriteGo;

class Cookie :
	public GameObject
{
protected:
	sf::Sprite cookieOrigin;
	SpriteGo* cookiePtr;

	std::string texId;
	sf::Vector2f velocity = { 0.f,0.f };
	bool isBuffed = false;

	float buffTimer = 4.f;
	float gravity = 0.f;
	float speed = 100.f;

public:
	Cookie(const std::string& fontId = "", const std::string& name = "");
	virtual ~Cookie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetSpeed(float s) {
		speed = s;
	}

	float GetSpeed()
	{
		return speed;
	}

	bool BufferCheck(float dt);
	bool cookieJump(float dt);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

