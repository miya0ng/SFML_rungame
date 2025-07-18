#pragma once
#include "GameObject.h"
enum class JellyType { Basic, Yellow, Pink, Blue };

class Jelly :
    public GameObject
{
protected:
	int jellyValue = 112;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;

public:
	
	Jelly(const std::string& name = "");
	virtual ~Jelly() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetScore(int s) { jellyValue = s; }
	int GetScore() { return jellyValue; }
	void SetActive(bool a) { active = a; }
	bool GetActive() const { return active; }
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Reset(sf::Vector2f pos);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetType(JellyType type);
	sf::Sprite& GetSprite() { return sprites[static_cast<size_t>(curType)]; }
	sf::FloatRect GetLocalBounds(JellyType t) const
	{
		return sprites[static_cast<size_t>(t)].getLocalBounds();
	}
	sf::FloatRect GetGlobalBounds(JellyType t) const
	{
		return sprites[static_cast<size_t>(t)].getGlobalBounds();
	}

protected:
	std::vector<sf::Sprite> sprites;
	sf::Sprite jellySprite;
	JellyType curType{ JellyType::Yellow };
};

