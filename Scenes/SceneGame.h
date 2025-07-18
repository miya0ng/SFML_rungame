#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "HitBox.h"

class UiHud;
class HitBox;	
class Jelly;
class Obstacle;
class Pattern1;
class AniPlayer;
class Background;
class SceneGame :
    public Scene
{
protected:
	float scrollSpeed = 100.f;
	float backgroundWidth;
	float scrollOffset =0.f;
	float offsetX = 0;
	float collisionTimer = 0.f;
	bool getMagnet = false;
	bool isCollision = false;
	int playerHp = 0;
	int playerMaxHp = 0;
	int jellyScore = 1000000;

	Jelly* jellyPtr;
	Obstacle* obstacle;
	AniPlayer* aniPlayer;
	Background* bg;
	Pattern1* pattern1;
	UiHud* uiHud;

	bool isGameOver = false;

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