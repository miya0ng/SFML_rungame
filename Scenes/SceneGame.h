#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Jelly;
class Obstacle;
class Pattern1;
class AniPlayer;
class Background;
class SceneGame :
    public Scene
{
protected:
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;

	float scrollSpeed = 100.f;
	float backgroundWidth;
	float scrollOffset =0.f;
	float offsetX = 0;

	bool getMagnet = false;

	int jellyScore = 0;

	Jelly* jellyPtr;
	Obstacle* obstacle;
	AniPlayer* aniPlayer;
	Background* bg;
	Pattern1* pattern1;

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