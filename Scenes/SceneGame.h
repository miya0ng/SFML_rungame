#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "HitBox.h"
#include <queue>  

class UiHud;
class Jelly;
class Obstacle;
class PatternBase;
class Pattern1;
class Pattern2;
class AniPlayer;
class Background;
class SceneGame :
	public Scene
{
protected:
	float hpTimer = 0.f;
	const float hpDrainDuration = 120.f;

	float scrollSpeed = 0.f;
	float backgroundWidth;
	float scrollOffset = 0.f;
	float offsetX = 0;
	float collisionTimer = 0.f;
	float hpBarTimer = 0.f;
	bool getMagnet = false;
	bool isCollision = false;
	int playerHp = 0;
	int playerMaxHp = 0;
	int jellyScore = 1000000;
	int coinScore = 0;

	std::vector<PatternBase*> patterns;
	size_t currentIndex = 0;
	PatternBase* currentPattern = nullptr;
	std::queue<PatternBase*> patternQueue;

	Jelly* jellyPtr = nullptr;
	Obstacle* obstacle = nullptr;
	AniPlayer* aniPlayer = nullptr;
	Background* bg = nullptr;
	Pattern1* pattern1 = nullptr;
	Pattern2* pattern2 = nullptr;
	UiHud* uiHud = nullptr;

	bool isGameOver = false;

	sf::Sprite background1;
	sf::Sprite background2;
	sf::Texture backgroundTexture;

public:
	SceneGame();
	~SceneGame();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
	void Release()override;
};