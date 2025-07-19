#pragma once
#include "PatternBase.h"
#include "Platform.h"
#include "Jelly.h"
class Coin;
class Obstacle;
class Jelly;
class Platform;
class AniPlayer;
class Pattern1 :
    public PatternBase
{
protected:
	struct ArchParam
	{
		float     radius;   // ¹ÝÁö¸§
		int       count;    // Á©¸® °³¼ö
		JellyType type;     // Á©¸® »ö
	};

	std::vector<ArchParam> archTable{
		{  60.f, 10, JellyType::Yellow },
		{ 100.f, 14, JellyType::Blue   },
		{  80.f, 12, JellyType::Pink   }
	};

	enum class JellyPattern {
		Straight, Arch, Zigzag,
		Wave, StairsUp, StairsDown, CustomArch
	};
	enum class CoinPattern {
		Straight, Arch, Zigzag,
		Ring, Cluster, VerticalLine
	};

	std::vector<JellyPattern> jellyQueue;
	std::vector<CoinPattern> coinQueue;
	size_t currJellyIndex = 0;
	size_t currCoinIndex = 0;
	size_t archIdx = 0;

	sf::Vector2f tilePos;
	sf::Vector2f jellyPos;
	sf::Vector2f conePos;
	sf::Vector2f coinPos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

	Platform* tiles = nullptr;
	AniPlayer* aniPlayer = nullptr;
	Jelly* jellys = nullptr;
	Obstacle* cones = nullptr;
	Coin* coins = nullptr;

	float dir = -1.f;
	float tileSpawnX = 0.f;
	float tileSpawnY = FRAMEWORK.GetWindowBounds().height - 80.f;
	float jellySpawnX = 300.f;
	float jellySpawnY = 220.f;
	float coinSpawnX = 350.f;
	float coinSpawnY = 220.f;
	float jellySpacing = 50.f;
	float coinSpacing = 50.f;
	float coneSpawnX = 1782.f;
	float coneSpawnY = FRAMEWORK.GetWindowBounds().height - 79.f;

public:
	std::vector<Platform*> activeTileList;
	std::vector<Platform*> pooledTileList;
	std::vector<Obstacle*> activeConeList;
	std::vector<Obstacle*> pooledConeList;
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;
	std::vector<Coin*> activeCoinList;
	std::vector<Coin*> pooledCoinList;

	Pattern1();
	~Pattern1();

	void Init();
	void Release();
	void Reset();
	void Update(float dt, float playerSpeed);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SpawnStraight();
	void SpawnArch();
	void SpawnZigzag();
	void SpawnStairsUp();
	void SpawnStairsDown();
	void SpawnArchJellies();

	void SpawnCoinsStraight();
	void SpawnCoinsArch();
	void SpawnCoinsZigzag();
	void SpawnNextChunk();
	void SpawnCoinsRing();
	void SpawnCoinsCluster();
	void SpawnCoinsVertical();

	std::vector<Jelly*>& GetJellies() override { return activeJellyList; }
	std::vector<Coin*>& GetCoins() override { return activeCoinList; }
	std::vector<Obstacle*>& GetObstacles() override { return activeConeList; }
	bool IsFinished() const {
		if (activeTileList.empty())
			return true;
		float lastX = activeTileList.back()->GetPosition().x;
		float screenW = FRAMEWORK.GetWindowBounds().width;
		return lastX <= screenW;
	}
};