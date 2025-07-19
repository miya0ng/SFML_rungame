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

void SceneGame::Init()
{
	// ���� Font assets ��������������������������������������������������������������������������������������������
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/CookieRun Bold.ttf");

	// ���� Texture assets ������������������������������������������������������������������������������������������
	texIds.push_back("graphics/silverCoin.png");
	texIds.push_back("graphics/goldCoin.png");
	texIds.push_back("graphics/jelly1.png");
	texIds.push_back("graphics/jelly2.png");
	texIds.push_back("graphics/jelly3.png");
	texIds.push_back("graphics/jelly4.png");
	texIds.push_back("graphics/silverCoin.png");
	texIds.push_back("graphics/lifeBar.png");
	texIds.push_back("graphics/lifeBar1.png");
	texIds.push_back("graphics/jumpno.png");
	texIds.push_back("graphics/slideno.png");
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/player_origin.png");
	texIds.push_back("graphics/player_jump.png");
	texIds.push_back("graphics/player_double_jump.png");
	texIds.push_back("graphics/player_slide.png");

	// ���� Animation clips ����������������������������������������������������������������������������������������
	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/cookierun.csv");
	ANI_CLIP_MGR.Load("animations/cookiejump.csv");
	ANI_CLIP_MGR.Load("animations/doublejump.csv");
	ANI_CLIP_MGR.Load("animations/cookieslide.csv");

	std::cout << "SceneGame Init()" << std::endl;

	// ���� UI elements ����������������������������������������������������������������������������������������������
	TextGo* startText = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	startText->SetString("Start");
	startText->SetCharacterSize(30);
	startText->SetFillColor(sf::Color::White);
	startText->sortingLayer = SortingLayers::UI;
	startText->sortingOrder = 0;
	AddGameObject(startText);

	uiHud = new UiHud();
	AddGameObject(uiHud);

	// ���� World objects ��������������������������������������������������������������������������������������������
	bg = new Background();
	aniPlayer = static_cast<AniPlayer*>(AddGameObject(new AniPlayer()));
	bg->SetPlayer(aniPlayer);
	bg->Init();

	obstacle = new Obstacle("cone1");
    pattern1 = new Pattern1();
    pattern2 = new Pattern2();
    patterns.push_back(pattern1);
    patterns.push_back(pattern2);
    playerMaxHp = aniPlayer->GetHp();
    for (auto* p : patterns)
        p->Init();
	Scene::Init();
}

void SceneGame::Enter()
{
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
    Scene::Update(dt);
	playerHp = aniPlayer->GetHp();

    // ���� HUD ������������������������������������������������������������������������������������������������������
    uiHud->SetScoreText(jellyScore);
    uiHud->SetCoinText(coinScore);
    uiHud->SetHpRatio(static_cast<float>(playerHp) / playerMaxHp);

    // ���� World updates ��������������������������������������������������������������������������������������������
    bg->Update(dt);

    //pattern2->Update(dt, aniPlayer->GetSpeed());
    for (auto* pattern : patterns)
    {
        pattern->Update(dt, aniPlayer->GetSpeed());
    }

    // Jelly collisions
    for (auto it = patterns[0]->GetJellies().begin(); it != patterns[0]->GetJellies().end(); )
    {
        if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
        {
            if (!getMagnet)
            {
                // TODO: magnet effect
            }
            jellyScore += (*it)->GetScore();
            (*it)->SetActive(false);
            it = patterns[0]->GetJellies().erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Coin collisions
    for (auto it = patterns[0]->GetCoins().begin(); it != patterns[0]->GetCoins().end(); )
    {
        //  std::cout << "." << coinScore << std::endl;
        if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
        {
            //std::cout << "coin: " << (*it)->GetScore() <<", " << coinScore << std::endl;
            if (!getMagnet)
            {
                // TODO: magnet effect
            }
            coinScore += (*it)->GetScore();
            (*it)->SetActive(false);
            it = pattern1->activeCoinList.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Damage cooldown timer
    if (isCollision)
        collisionTimer += dt;

    if (collisionTimer >= 1.2f)
    {
        isCollision = false;
        collisionTimer = 0.f;
    }

    // Cone collisions
    for (auto it = patterns[0]->GetObstacles().begin(); it != patterns[0]->GetObstacles().end(); )
    {
        Obstacle* cone = *it;

        sf::Vector2f coneOffset = { cone->GetSprite().getGlobalBounds().width * 0.5f,
                                      cone->GetSprite().getGlobalBounds().height * 0.5f };
        sf::Vector2f playerOffset = { aniPlayer->GetSprite().getGlobalBounds().width * 0.5f, 0.f };

        if (Utils::Distance(cone->GetPosition() + coneOffset,
            aniPlayer->GetPosition() + playerOffset) <= 50.f && !isCollision)
        {
            isCollision = true;
            playerHp -= cone->GetDamage();
            //std::cout << "Player Hp: " << playerHp << std::endl;

            if (playerHp <= 0)
            {
                isGameOver = true;
                aniPlayer->SetActive(false);
                aniPlayer->SetSpeed(0.f);
                std::cout << "GameOver" << playerHp << std::endl;
            }
            else
            {
                aniPlayer->SetHp(playerHp);
                //std::cout << "Player Hp2: " << playerHp << std::endl;
            }
        }
        else
        {
            ++it;
        }
    }

    // ���� Scene transitions ����������������������������������������������������������������������������������
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
	patterns[0]->Draw(window);
	Scene::Draw(window);
}