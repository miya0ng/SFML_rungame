#pragma once
#include "GameObject.h"
class Jelly :
    public GameObject
{
protected:
	
	sf::Texture spriteTexture;
	int jellyValue = 0;

public:
	sf::Sprite sprite;
	Jelly(const std::string& name = "");
	virtual ~Jelly() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::Sprite& GetSprite() { return sprite; }
	int GetScore() { return jellyValue=10; }

	bool GetActive() const { return active; }
	void SetActive(bool a) { active = a; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Reset(sf::Vector2f pos);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

