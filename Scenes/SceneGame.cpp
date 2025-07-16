#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "AniPlayer.h"
#include "Background.h"
#include "StageManager.h"
#include "Obstacle.h"
#include "Jelly.h"
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
	texIds.push_back("img/Objectimg/map1img/platform1.png");
	texIds.push_back("img/Objectimg/map1img/jelly2.png");

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
	aniPlayer=(AniPlayer*)AddGameObject(new AniPlayer());
	bg->SetPlayer(aniPlayer);	
	bg->Init();
	stageManager = new StageManager(activeJellyList, pooledJellyList);
	stageManager->Init();			
	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({center});
	
	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	//if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	//{
	//	sf::Vector2i mouse = InputMgr::GetMousePosition();
	//	std::cout << mouse.x << ", " << mouse.y << std::endl;
	//}
	//-------------------------------------------------backgroundScroll

	bg->Update(dt);

	//-------------------------------------------------stageManagerUpdate
	//-----------------jellySpawn / platformSpawn

	stageManager->Update(dt, aniPlayer->GetSpeed());

	//--------------------------------------------collisionCheck
	
	for (auto it = stageManager->activeJellyList.begin(); it != stageManager->activeJellyList.end(); )
	{
		if (Utils::CheckCollision((*it)->GetSprite(), aniPlayer->GetSprite()))
		{
			/*if (!getMagnet)
			{
			    //나중에 해야지?
			}*/
			jellyScore += (*it)->GetScore();
			(*it)->SetActive(false);
			it = stageManager->activeJellyList.erase(it);
			std::cout << "Jelly Score: " << jellyScore << std::endl;
		}
		else
		{
			++it;
		}
	}
	
	//-------------------------------------------------nextScene

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	bg->Draw(window);
	stageManager->Draw(window);
		Scene::Draw(window);
}