
#include "stdafx.h"
#include "Pattern1.h"
#include "Jelly.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Coin.h"

Pattern1::Pattern1()
	: tiles(nullptr), aniPlayer(nullptr), jellys(nullptr),
	cones(nullptr), coins(nullptr)
{

}

Pattern1::~Pattern1()
{
	for (auto j : pooledJellyList)  delete j;
	for (auto j : activeJellyList)  delete j;
	for (auto t : pooledTileList)   delete t;
	for (auto t : activeTileList)   delete t;
	for (auto o : pooledConeList)   delete o;
	for (auto o : activeConeList)   delete o;
}

void Pattern1::Init()
{
	tileTexture.loadFromFile("graphics/platform.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);

	int tileCount = 350;
	for (int i = 0; i < tileCount; ++i)
	{
		tiles = new Platform();
		tileSpawnX = activeTileList.empty() ? 0.f : activeTileList.back()->GetPosition().x + tileSprite.getGlobalBounds().width;
		tiles->SetActive(true);
		tiles->Init();
		tiles->SetPosition({ tileSpawnX,  tileSpawnY });
		//tiles->SetScale({ 0.7f, 0.7f });
		activeTileList.push_back(tiles);
	}

	float spacing = 700.f;
	int coneCount = 4;
	for (int i = 0; i < coneCount; ++i)
	{
		cones = new Obstacle("cone");
		cones->SetActive(true);
		cones->Init();
		cones->SetPosition({ coneSpawnX + i * spacing, coneSpawnY });
		cones->SetOrigin(Origins::BC);

		activeConeList.push_back(cones);
	}

	jellyQueue.clear();
	jellyQueue.push_back(JellyPattern::Straight);
	jellyQueue.push_back(JellyPattern::Arch);
	//jellyQueue.push_back(JellyPattern::CustomArch);
	jellyQueue.push_back(JellyPattern::Arch);
	jellyQueue.push_back(JellyPattern::Arch);
	jellyQueue.push_back(JellyPattern::StairsDown);
	jellyQueue.push_back(JellyPattern::Zigzag);
	jellyQueue.push_back(JellyPattern::StairsUp);

	coinQueue.clear();
	coinQueue.push_back(CoinPattern::Arch);
	coinQueue.push_back(CoinPattern::Arch);
	coinQueue.push_back(CoinPattern::Straight);
	coinQueue.push_back(CoinPattern::Straight);
	//coinQueue.push_back(CoinPattern::Zigzag);
	//coinQueue.push_back(CoinPattern::VerticalLine);
	//coinQueue.push_back(CoinPattern::Cluster);
	coinQueue.push_back(CoinPattern::Ring);
	coinQueue.push_back(CoinPattern::Ring);
	coinQueue.push_back(CoinPattern::Zigzag);
	currCoinIndex = 0;
	currJellyIndex = 0;

	SpawnNextChunk();
}

void Pattern1::Release()
{

}
void Pattern1::Reset()
{

}
void Pattern1::Update(float dt)
{

}
void Pattern1::Update(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tilePooledTriggerX = FRAMEWORK.GetWindowBounds().width;
	for (auto it = activeTileList.begin(); it != activeTileList.end(); )
	{
		auto tile = *it;
		tilePos = tile->GetPosition();
		tilePos.x += dt * playerSpeed * dir;
		tile->SetPosition({ tilePos.x, tile->GetPosition().y });

		if (tilePos.x < -tileWidth)
		{
			tile->SetActive(false);
			pooledTileList.push_back(tile);
			it = activeTileList.erase(it);
		}
		else
		{
			++it;
		}
	}

	//----------------------------------------------------------------------------NextPattern
	if (!activeJellyList.empty())
	{
		float jellyWidth = activeJellyList.front()->GetSprite()
			.getGlobalBounds().width;

		float jellyPooledTriggerX = FRAMEWORK.GetWindowBounds().left - jellyWidth;

		for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
		{
			auto jelly = *it;
			jellyPos = jelly->GetPosition();
			jellyPos.x += dt * playerSpeed * dir;
			jelly->SetPosition(jellyPos);

			if (jellyPos.x < jellyPooledTriggerX)
			{
				jelly->SetActive(false);
				pooledJellyList.push_back(jelly);
				it = activeJellyList.erase(it);
			}
			else ++it;
		}
	}

	float coneWidth = cones->GetSprite().getGlobalBounds().width;
	float conePooledTriggerX = FRAMEWORK.GetWindowBounds().left - coneWidth;
	for (auto it = activeConeList.begin(); it != activeConeList.end(); )
	{
		auto cone = *it;
		conePos = cone->GetPosition();
		conePos.x += dt * playerSpeed * dir;
		cone->SetPosition(conePos);

		if (conePos.x < -conePooledTriggerX-200.f)
		{
			cone->SetActive(false);
			pooledConeList.push_back(cone);
			it = activeConeList.erase(it);
		}
		else
		{
			++it;
		}
	}

	//float coneWidth = cones->GetSprite().getGlobalBounds().width;
	float coinPooledTriggerX = FRAMEWORK.GetWindowBounds().left - 50.f;
	for (auto it = activeCoinList.begin(); it != activeCoinList.end(); )
	{
		auto coin = *it;
		coinPos = coin->GetPosition();
		coinPos.x += dt * playerSpeed * dir;
		
		coin->SetPosition(coinPos);

		if (coinPos.x < coinPooledTriggerX)
		{
			coin->SetActive(false);
			pooledCoinList.push_back(coin);
			it = activeCoinList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (activeJellyList.back()->GetPosition().x<= FRAMEWORK.GetWindowBounds().width+50.f)
	{
		jellySpawnX = FRAMEWORK.GetWindowBounds().width + 50.f;
		coinSpawnY = 220.f;
		SpawnNextChunk();
	}
}

void Pattern1::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTileList)
	{
		if (t->GetActive())
		{
			t->Draw(win);
		}
	}

	for (auto* j : activeJellyList)
	{
		if (j->GetActive())
		{
			j->Draw(win);
		}
	}

	for (auto* t : activeConeList)
	{
		if (t->GetActive())
		{
			t->Draw(win);
		}
	}

	for (auto* t : activeCoinList)
	{
		if (t->GetActive())
		{
			t->Draw(win);
		}
	}
}

void Pattern1::SpawnStraight()
{
	const int jellyCount = 30;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellys->SetActive(true);
		jellySpawnX += jellySpacing;
		jellySpawnY = 220.f;
		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		if (i % 5 == 0)
		{
			jellys->SetType(JellyType::Blue);
		}
		else if (i % 3 == 0)
		{
			jellys->SetType(JellyType::Yellow);
		}
		else
		{
			jellys->SetType(JellyType::Basic);
		}
		activeJellyList.push_back(jellys);
	}
}

void Pattern1::SpawnArch()
{
	const int jellyCount = 12;
	const float jellyRadius = 80.f;
	const float centerX = jellySpawnX*2.f + jellyRadius;
	const float centerY = 220.f;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellys->SetActive(true);
		float t = static_cast<float>(i) / (jellyCount - 1);
		float theta = 3.14159265f * t;

		float x = centerX + jellyRadius * std::cos(theta);
		float y = centerY - jellyRadius * std::sin(theta);

		jellys->SetPosition({ x, y });
		jellys->SetType(JellyType::Yellow);
		activeJellyList.push_back(jellys);
	}
	jellySpawnX = centerX + jellyRadius;
}

void Pattern1::SpawnZigzag()
{
	const int jellyCount = 20;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellys->SetActive(true);
		jellySpawnX += jellySpacing;
		jellySpawnY = (i % 2 == 0) ? 200.f : 240.f;

		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		jellys->SetType(JellyType::Blue);
		activeJellyList.push_back(jellys);
	}
}

// ─── Jelly: 계단 위로 ─────────────────────────────────────────
void Pattern1::SpawnStairsUp()
{
	const int step = 5;  const int count = 3;
	for (int i = 0; i < count; ++i)
	{
		jellys = new Jelly();  jellys->Init();
		jellys->SetActive(true);

		jellySpawnX += jellySpacing;
		float y = 200.f - i * step;

		jellys->SetPosition({ jellySpawnX, y });
		jellys->SetType(JellyType::Blue);
		activeJellyList.push_back(jellys);
	}
}

// ─── Jelly: 계단 ↓ ────────────────────────────────────────────
void Pattern1::SpawnStairsDown()
{
	const int step = 10;  const int count = 5;
	for (int i = 0; i < count; ++i)
	{
		jellys = new Jelly();  jellys->Init();
		jellys->SetActive(true);

		jellySpawnX += jellySpacing;
		jellySpawnY= 200.f+ i * step;

		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		jellys->SetType(JellyType::Pink);
		activeJellyList.push_back(jellys);
	}
}

void Pattern1::SpawnArchJellies()
{
	const ArchParam& P = archTable[archIdx];
	archIdx = (archIdx + 1) % archTable.size();
	float radius = P.radius;
	int   count = P.count;
	float spacing = jellySpacing;
	JellyType tp = P.type;

	float cx = jellySpawnX + radius;
	float cy = jellySpawnY;

	for (int i = 0; i < count; ++i)
	{
		Jelly* j = new Jelly();
		j->Init();  j->SetActive(true);  j->SetOrigin(Origins::MC);

		float t = static_cast<float>(i) / (count - 1);
		float theta = 3.14159265f * (1.f - t);

		float x = cx + radius * std::cos(theta);
		float y = cy - radius * std::sin(theta);

		j->SetPosition({ x, y });
		j->SetType(tp);

		if (i % 3 == 0)
		{
			jellys->SetType(JellyType::Yellow);
			if (i % 10 == 0 || i % 9 == 0)
			{
				jellys->SetType(JellyType::Blue);
			}
		}
		if (!activeJellyList.empty() && activeJellyList.back()->GetPosition().y <= 150.f)
		{
			jellys->SetType(JellyType::Pink);
		}
		else jellys->SetType(JellyType::Basic);
		activeJellyList.push_back(j);
	}
	jellySpawnX = jellySpawnX + radius + spacing;
}

void Pattern1::SpawnCoinsStraight()
{
	const int coinCount = 10;
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coins->Reset();
		coins->SetActive(true);
		coinSpawnX += coinSpacing;
		coins->SetPosition({ coinSpawnX, coinSpawnY });
		coins->SetType(CoinType::Silver);
		activeCoinList.push_back(coins);
	}
}

void Pattern1::SpawnCoinsArch()
{
	const int coinCount = 10;
	const float coinRadius = 50.f;
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coins->Reset();
		coins->SetActive(true);
		coinSpawnX += coinSpacing;

		float t = float(i) / (coinCount - 1);
		float angle = 3.14159265f * t;
		coinSpawnY = 200.f - coinRadius * std::sin(angle);

		coins->SetPosition({ coinSpawnX, coinSpawnY });
		coins->SetType(i % 2 == 0 ? CoinType::Gold : CoinType::Silver);
		activeCoinList.push_back(coins);
	}
}

void Pattern1::SpawnCoinsZigzag()
{
	const int coinCount = 20;
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coins->Reset();
		coins->SetActive(true);
		coinSpawnX += 35;
		coinSpawnY = (i % 2 == 0) ? 200.f : 240.f;
		i % 4 == 0 ? coins->SetType(CoinType::Silver) : coins->SetType(CoinType::Gold);
		coins->SetPosition({ coinSpawnX, coinSpawnY });
		activeCoinList.push_back(coins);
	}
}

// ─── Coins: 원형 링 ───────────────────────────────────────────
void Pattern1::SpawnCoinsRing()
{
	const int num = 12;
	const float rad = 40.f;
	const sf::Vector2f center{ coinSpawnX + rad, coinSpawnY - rad };

	for (int i = 0; i < num; ++i)
	{
		coins = new Coin("coin"); coins->Init(); coins->SetActive(true);

		float angle = 2 * 3.14159265f * i / num;
		coinSpawnX = center.x + rad * std::cos(angle);
		coinSpawnY = center.y + rad * std::sin(angle);

		coins->SetPosition({ coinSpawnX, coinSpawnY });
		coins->SetType(i % 4 == 0 ? CoinType::Gold : CoinType::Silver);
		activeCoinList.push_back(coins);
	}
	coinSpawnX += rad * 2;
}

// ─── Coins: 3×3 클러스터 ─────────────────────────────────────
void Pattern1::SpawnCoinsCluster()
{
	const float spacing = 18.f;
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
		{
			coins = new Coin("coin"); coins->Init(); coins->SetActive(true);

			coinSpawnX = coinSpawnX + c * spacing;
			coinSpawnY = coinSpawnY - r * spacing;

			coins->SetPosition({ coinSpawnX, coinSpawnY });
			coins->SetType((r == 1 && c == 1) ? CoinType::Gold : CoinType::Silver);
			activeCoinList.push_back(coins);
		}
	coinSpawnX += 1.2f * spacing;
}

// ─── Coins: 세로 줄 ───────────────────────────────────────────
void Pattern1::SpawnCoinsVertical()
{
	const int num = 6;
	for (int i = 0; i < num; ++i)
	{
		coins = new Coin("coin"); coins->Init(); coins->SetActive(true);

		coinSpawnY -= i * 15.f;
		coins->SetPosition({ coinSpawnX, coinSpawnY });
		coins->SetType(CoinType::Silver);
		activeCoinList.push_back(coins);
	}
	coinSpawnX += coinSpacing;
}

void Pattern1::SpawnNextChunk()
{
	if (jellyQueue.empty()) return;
	if (coinQueue.empty()) return;

	JellyPattern jp = jellyQueue[currJellyIndex];
	currJellyIndex = (currJellyIndex + 1) % jellyQueue.size();

	CoinPattern cp = coinQueue[currCoinIndex];
	currCoinIndex = (currCoinIndex + 1) % coinQueue.size();

	switch (jp)
	{
	case JellyPattern::Straight:SpawnStraight(); break;
	case JellyPattern::Arch:SpawnArch(); break;
	case JellyPattern::Zigzag:SpawnZigzag(); break;
	case JellyPattern::StairsUp:SpawnStairsUp();break;
	case JellyPattern::StairsDown:SpawnStairsDown();break;
	case JellyPattern::CustomArch:SpawnArchJellies(); break;
	}

	switch (cp)
	{
	case CoinPattern::Straight:SpawnCoinsStraight(); break;
	case CoinPattern::Arch:SpawnCoinsArch(); break;
	case CoinPattern::Zigzag:SpawnCoinsZigzag(); break;
	case CoinPattern::Ring:SpawnCoinsRing();break;
	case CoinPattern::Cluster:SpawnCoinsCluster();break;
	case CoinPattern::VerticalLine:SpawnCoinsVertical();break;
	}
	/*todo:tile/coin */
}