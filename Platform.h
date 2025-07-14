#pragma once
#include "GameObject.h"

class AniPlayer;
class Platform :
    public GameObject
{
protected:
	AniPlayer* aniPlayer;
	TileType type = TileType::Ground;
	sf::Sprite sprite;

	sf::Vector2f position = { 0.f, 0.f };	
	static std::unordered_map<TileType, const sf::Texture*> texMap;

public:
	Platform(const std::string& name = "");
	virtual ~Platform() = default;
	void Move(const sf::Vector2f& delta)override
	{
		position += delta;
	}
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	sf::FloatRect GetGlobalBounds() const override {
		return sprite.getGlobalBounds();
	}
	void SetType(TileType t);
	TileType GetType() const { return type; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

