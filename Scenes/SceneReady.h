#pragma once
#include "Scene.h"
class SceneReady :
    public Scene
{
protected:
	sf::Vector2f mouseWorldPos;
	sf::RectangleShape button;
	sf::Sound* startSfx = nullptr;
	bool isButtonPressed = false;

public:
	SceneReady();
	~SceneReady() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

