#pragma once
#include "Animator.h"
#include "Hitbox.h"

class platform;
class AniPlayer : public GameObject
{
protected:
	Animator animator;
	sf::Sprite body;

	sf::Vector2f gravity = { 0.f, 1300.f };
	sf::Vector2f velocity = { 0.f, 0.f };

	float buffTimer = 4.f;
	bool isBuffed = false;
	bool isGrounded = true;
	int hp = 1000;
	int jumpCount = 0;
	float speed = 320.f;

	HitBox hitbox;

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
	void SetHp(int h) { hp = h; };
	int GetHp() const { return hp;}

	bool BufferCheck(float dt);
	bool cookieJump();
	bool cookieDoubleJump();
	bool cookieSlide();

	sf::Sprite GetSprite() { return body; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const
	{
		return body.getGlobalBounds();
	}
	HitBox& GetHitbox() { return hitbox; }
};
