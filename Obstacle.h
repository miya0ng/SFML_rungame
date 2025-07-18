#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Obstacle :
    public GameObject
{
protected:
	sf::Sprite obstacle;
	sf::Texture texture;

	int damage = 30;

public:
	HitBox hitbox;

    Obstacle(const std::string& name);
	virtual ~Obstacle() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	virtual void Move(const sf::Vector2f& delta)
	{
		position += delta;
	}
	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool GetActive() const { return active; }
	void SetActive(bool a) { active = a; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	int GetDamage() { return damage; }

	 sf::FloatRect GetLocalBounds() const
	{
		 return obstacle.getLocalBounds();
	}

	 sf::FloatRect GetGlobalBounds() const
	{
		 return obstacle.getGlobalBounds();
	}

	sf::Sprite GetSprite() { return obstacle; }
	const HitBox& GetHitBox() const { return hitbox; }
};