#pragma once
#include "Scene.h"

class Cookie;
class SceneTitle :
    public Scene
{
protected:
	Cookie* cookie;
public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

