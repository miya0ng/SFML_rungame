#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "AniPlayer.h"
#include "Background.h"
#include "Obstacle.h"
#include "Jelly.h"
#include "PatternBase.h"
#include "Pattern1.h"
#include "Pattern2.h"
#include "UiHud.h"	
#include "Coin.h"
#include <cmath>

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{

}

SceneGame::~SceneGame()
{
    Release();
}

void SceneGame::Init()
{
	// ── Font assets ──────────────────────────────────────────────
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/CookieRun Bold.ttf");

	// ── Texture assets ─────────────────────────────────────────────
	texIds.push_back("graphics/silverCoin.png");
	texIds.push_back("graphics/goldCoin.png");
	texIds.push_back("graphics/jelly1.png");
	texIds.push_back("graphics/jelly2.png");
	texIds.push_back("graphics/jelly3.png");
	texIds.push_back("graphics/jelly4.png");
	texIds.push_back("graphics/silverCoin.png");
	texIds.push_back("graphics/lifeBar.png");
	texIds.push_back("graphics/lifeBar1.png");
	texIds.push_back("graphics/jumpim.png");
	texIds.push_back("graphics/jumpno.png");
	texIds.push_back("graphics/slideim.png");
	texIds.push_back("graphics/slideno.png");
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/player_origin.png");
	texIds.push_back("graphics/player_jump.png");
	texIds.push_back("graphics/player_double_jump.png");
	texIds.push_back("graphics/player_slide.png");

    // ── Sound ────────────────────────────────────────────
    SOUNDBUFFER_MGR.Load("bgm/main.ogg");
    SOUNDBUFFER_MGR.Load("bgm/end.ogg");
    SOUNDBUFFER_MGR.Load("bgm/coin.ogg");
    SOUNDBUFFER_MGR.Load("bgm/jump.ogg");
    SOUNDBUFFER_MGR.Load("bgm/slide.ogg");
    soundIds.push_back("bgm/main.ogg");
    soundIds.push_back("bgm/end.ogg");
    soundIds.push_back("bgm/coin.ogg");
    soundIds.push_back("bgm/jump.ogg");
    soundIds.push_back("bgm/slide.ogg");
	// ── Animation clips ────────────────────────────────────────────
	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/cookierun.csv");
	ANI_CLIP_MGR.Load("animations/cookiejump.csv");
	ANI_CLIP_MGR.Load("animations/doublejump.csv");
	ANI_CLIP_MGR.Load("animations/cookieslide.csv");
	std::cout << "SceneGame Init()" << std::endl;

	// ── UI elements ───────────────────────────────────────────────
	TextGo* startText = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	startText->SetString("Start");
	startText->SetCharacterSize(30);
	startText->SetFillColor(sf::Color::White);
	startText->sortingLayer = SortingLayers::UI;
	startText->sortingOrder = 0;
	AddGameObject(startText);

	uiHud = new UiHud();
	AddGameObject(uiHud);

	// ── World objects ──────────────────────────────────────────────
	bg = new Background();
	aniPlayer = static_cast<AniPlayer*>(AddGameObject(new AniPlayer()));
	bg->SetPlayer(aniPlayer);
	bg->Init();

	obstacle = new Obstacle("cone1");

    // ── Pattern ──────────────────────────────────────────────
    pattern1 = new Pattern1();
    pattern2 = new Pattern2();
    patterns.push_back(pattern1);
    patterns.push_back(pattern2);

    for (auto* p : patterns)
    {
        p->Init();
        patternQueue.push(p);
    }

    playerMaxHp = aniPlayer->GetHp();
    playerHp = playerMaxHp;
    currentPattern = patterns.front();
    
	Scene::Init();
}

void SceneGame::Enter()
{
    SOUND_MGR.PlayBgm("bgm/game.wav",true);
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ center });
	
	Scene::Enter();
}

void SceneGame::Update(float dt)
{
    bool jumpPressed = InputMgr::GetKey(sf::Keyboard::W);
    bool slidePressed = InputMgr::GetKey(sf::Keyboard::S);

    uiHud->UpdateButtons(jumpPressed, slidePressed);

    Scene::Update(dt);
    hpTimer += dt;
    float ratio = std::max(1.f - hpTimer / hpDrainDuration, 0.f);
    int drainHp = static_cast<int>(playerMaxHp * std::max(1.f - hpTimer / 60.f, 0.f));
    if (playerHp > drainHp) playerHp = drainHp;

    // ── HUD ───────────────────────────────────────────────────
    uiHud->SetScoreText(jellyScore);
    uiHud->SetCoinText(coinScore);
    uiHud->SetHpRatio(static_cast<float>(playerHp) / playerMaxHp);

    // ── World updates ──────────────────────────────────────────────
    bg->Update(dt);
    currentPattern->Update(dt, aniPlayer->GetSpeed());

    aniPlayer->SetHp(playerHp);
    
    if (currentPattern->IsFinished())
    {
        patternQueue.pop();
        patternQueue.push(currentPattern);
        currentPattern = patternQueue.front();
        currentPattern->Init();
    }

    // ── Check collisions ─────────────────────────────────────────────
    auto& jellies = currentPattern->GetJellies();
    auto& coins = currentPattern->GetCoins();
    auto& obstacles = currentPattern->GetObstacles();

    // Jelly collisions
    for (auto it = jellies.begin(); it != jellies.end(); )
    {
        if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
        {
            jellyScore += (*it)->GetScore();
            (*it)->SetActive(false);
            it = jellies.erase(it);
        }
        else ++it;
    }

    for (auto it = coins.begin(); it != coins.end(); )
    {
        if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
        {
            coinScore += (*it)->GetScore();
            (*it)->SetActive(false);
            it = coins.erase(it);
        }
        else ++it;
    }

    // Cone collisions
    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        Obstacle* cone = *it;
        sf::Vector2f coneOff{ cone->GetSprite().getGlobalBounds().width * 0.5f,
                               cone->GetSprite().getGlobalBounds().height * 0.5f };
        sf::Vector2f plyOff{ aniPlayer->GetSprite().getGlobalBounds().width * 0.5f, 0.f };

        if (Utils::Distance(cone->GetPosition() + coneOff,
            aniPlayer->GetPosition() + plyOff) <= 50.f && !isCollision)
        {
            isCollision = true;
            playerHp -= cone->GetDamage();
            aniPlayer->SetHp(playerHp);
        }
        ++it;
    }
    
    if (aniPlayer->GetHp() <= 50.f)
    {
        isGameOver = true;
        aniPlayer->SetHp(50);
        aniPlayer->SetActive(false);
        aniPlayer->SetSpeed(0.f);
    }

    // Damage cooldown timer
    if (isCollision)
        collisionTimer += dt;

    if (collisionTimer >= 1.2f)
    {
        isCollision = false;
        collisionTimer = 0.f;
    }

    // ── Scene transitions ─────────────────────────────────────────
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter) || isGameOver)
    {
        isGameOver = false;
        SCENE_MGR.ChangeScene(SceneIds::GameOver);
    }

    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
    {
        sf::Vector2i mouse = InputMgr::GetMousePosition();
        std::cout << mouse.x << ", " << mouse.y << std::endl;
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	bg->Draw(window);
    currentPattern->Draw(window);
	Scene::Draw(window);
}

void SceneGame::Release()
{
    Scene::Release(); // AddGameObject로 추가한 것들 정리

    // UiHud, Background 정리
    if (uiHud)
    {
        delete uiHud;
        uiHud = nullptr;
    }

    if (bg)
    {
        delete bg;
        bg = nullptr;
    }

    // Obstacle은 사용하지 않는다면 삭제
    if (obstacle)
    {
        delete obstacle;
        obstacle = nullptr;
    }

    // Pattern 정리
    for (auto* p : patterns)
    {
        delete p;
    }
    patterns.clear();

    // 패턴 큐는 포인터 공유라서 개별 delete X
    while (!patternQueue.empty())
        patternQueue.pop();
}
