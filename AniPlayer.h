#pragma once
#include "Animator.h"

class AniPlayer : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f gravity = { 0.f, 1300.f };
	sf::Vector2f velocity = { 0.f, 0.f };

	float buffTimer = 4.f;

	bool isBuffed = false;
	bool isGrounded = true;

	float speed = 120.f;

public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetSpeed(float s)
	{
		speed = s;
	}

	float GetSpeed()
	{
		return speed;
	}

	bool BufferCheck(float dt);
	bool cookieJump();
	bool cookieSlide();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
