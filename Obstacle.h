#pragma once
#include "GameObject.h"

class Obstacle :
    public GameObject
{
protected:
	sf::Sprite obstacle;
	sf::Texture texture;

public:
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

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) { position = pos; }

	float GetRotation() const { return rotation; }
	void SetRotation(float rot) { rotation = rot; }

	sf::Vector2f GetScale() const { return scale; }
	void SetScale(const sf::Vector2f& s) { scale = s; }

	sf::Vector2f GetOrigin() const { return origin; }
	 void SetOrigin(const sf::Vector2f& o)
	{
		originPreset = Origins::Custom;
		origin = o;
	}
	 void SetOrigin(Origins preset) { originPreset = preset; }

	 sf::FloatRect GetLocalBounds() const
	{
		 return obstacle.getLocalBounds();
	}

	 sf::FloatRect GetGlobalBounds() const
	{
		 return obstacle.getGlobalBounds();
	}

};