#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "AniPlayer.h"
#include "Background.h"
#include "Obstacle.h"
#include "Jelly.h"
#include "Pattern1.h"
#include <cmath>

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{

}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/player_origin.png");
	texIds.push_back("graphics/player_jump.png");
	texIds.push_back("graphics/player_double_jump.png");
	texIds.push_back("graphics/player_slide.png");
	//texIds.push_back("graphics/platform.png");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/cookierun.csv");
	ANI_CLIP_MGR.Load("animations/cookiejump.csv");
	ANI_CLIP_MGR.Load("animations/doublejump.csv");
	ANI_CLIP_MGR.Load("animations/cookieslide.csv");
	std::cout << "sceneGame init()" << std::endl;
	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	go->SetString("Start");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	AddGameObject(go);

	//-------------------------------------------------cookieSet
	bg = new Background();
	aniPlayer = (AniPlayer*)AddGameObject(new AniPlayer());
	bg->SetPlayer(aniPlayer);
	bg->Init();
	obstacle = new Obstacle("cone1");
	pattern1 = new Pattern1();
	AddGameObject(pattern1);
	playerHp = aniPlayer->GetHp();
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

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mouse = InputMgr::GetMousePosition();
		std::cout << mouse.x << ", " << mouse.y << std::endl;
	}

	//--------------------------------------------------backgroundScroll

	bg->Update(dt);

	//-------------------------------------------------stageManagerUpdate
	//-----------------------------------------jellySpawn / platformSpawn

	pattern1->Update(dt, aniPlayer->GetSpeed());

	//----------------------------------------------------collisionCheck

	//std::cout << pattern1->activeJellyList.size() << std::endl;
	for (auto it = pattern1->activeJellyList.begin(); it != pattern1->activeJellyList.end(); )
	{
		if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
		{
			if (!getMagnet)
			{
				//나중에 해야지
			}
			jellyScore += (*it)->GetScore();
			(*it)->SetActive(false);
			it = pattern1->activeJellyList.erase(it);
			//std::cout << "Jelly Score: " << jellyScore << std::endl;
		}
		else
		{
			++it;
		}
	}
	if (isCollision)
	{
		collisionTimer += dt;
	}

	if (collisionTimer >= 1.2f)
	{
		isCollision = false;
		collisionTimer = 0.f;
	}

	for (auto it = pattern1->activeConeList.begin(); it != pattern1->activeConeList.end();)
	{
		Obstacle* cone = *it;
		sf::Vector2f coneOffset = { cone->GetSprite().getGlobalBounds().width * 0.5f, cone->GetSprite().getGlobalBounds().height * 0.5f };
		sf::Vector2f playerOffset = { aniPlayer->GetSprite().getGlobalBounds().width * 0.5f, 0};
		if (Utils::Distance(cone->GetPosition() + coneOffset, aniPlayer->GetPosition() + playerOffset) <= 50 && !isCollision)
		{
			isCollision = true;
			playerHp -= cone->GetDamage();
			std::cout << "Player Hp: " << playerHp << std::endl;
			if (playerHp <= 0)
			{
				isGameOver = true;
				aniPlayer->SetActive(false);
				aniPlayer->SetSpeed(0);
				std::cout << "GameOver" << playerHp << std::endl;
			}
			else
			{
				aniPlayer->SetHp(playerHp);
				std::cout << "Player Hp2: " << playerHp << std::endl;
			}
		}
		else
		{
			++it;
		}
	}

	//-------------------------------------------------nextScene

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter) || isGameOver)
	{
		isGameOver = false;
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	bg->Draw(window);
	pattern1->Draw(window);
	Scene::Draw(window);
}