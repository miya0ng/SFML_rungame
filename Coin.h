#pragma once
#include "GameObject.h"

enum class CoinType { Gold, Silver };
class Coin :
    public GameObject
{
protected:
	std::vector<sf::Sprite> sprites;
	sf::Sprite sprite;
	sf::Texture texture1;
	sf::Texture texture2;
public:
	Coin(const std::string& name = "");
	virtual ~Coin() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetType(CoinType type);
	sf::Sprite GetSprite() { return sprites[static_cast<size_t>(curType)]; }
	int GetScore() { return (curType == CoinType::Silver) ? 100 : 50;
	}
	CoinType curType{ CoinType::Silver };
};