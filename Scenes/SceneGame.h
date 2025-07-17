#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "HitBox.h"

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
	bool getMagnet = false;

	int playerHp = 1000;
	int jellyScore = 0;

	Jelly* jellyPtr;
	Obstacle* obstacle;
	AniPlayer* aniPlayer;
	Background* bg;
	Pattern1* pattern1;

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