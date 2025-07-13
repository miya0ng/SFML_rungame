#pragma once
class AniPlayer;
class Background 
{
protected:
	sf::Sprite background1;
	sf::Sprite background2;
	sf::Texture backgroundTexture;

	AniPlayer* aniPlayer;

	float scrollSpeed = 0.f;
	float backgroundWidth;
	float scrollOffset = 0.f;
	float offsetX = 0;
public:
	Background();
	virtual ~Background() = default;

	void SetPlayer(AniPlayer* p) { aniPlayer = p; };
	void Init();
	void Enter();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void Exit();
};

