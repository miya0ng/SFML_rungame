#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Cookie;

class SceneGame :
    public Scene
{
protected:
	//SpriteGo* backgrounds;
	float scrollSpeed = 0.f;
	float backgroundWidth;
	float scrollOffset =0.f;
	float offsetX = 0;
	sf::Sprite cookieOrigin;
	sf::Texture cookieTexture;

	Cookie* cookie=nullptr;

	sf::Sprite background1;
	sf::Sprite background2;
	sf::Texture backgroundTexture;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

