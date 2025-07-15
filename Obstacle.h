#pragma once
#include "GameObject.h"

class Obstacle :
    public GameObject
{
protected:


public:
    Obstacle(const std::string& name);
	virtual ~Obstacle() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};