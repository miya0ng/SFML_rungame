#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "AniPlayer.h"
#include <cmath>

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{

}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	texIds.push_back("img/Objectimg/map1img/bg1.png"); 
	//texIds.push_back("img/cookieimg/cookie1/player_attack.png");

	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/player_origin.png");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/cookierun.csv");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	go->SetString("Start");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	AddGameObject(go);

	backgroundTexture.loadFromFile("img/Objectimg/map1img/bg1.png");
	background1.setTexture(backgroundTexture);
	background2.setTexture(backgroundTexture);
	backgroundWidth = backgroundTexture.getSize().x;
	//-------------------------------------------------cookieSet

	aniPlayer=(AniPlayer*)AddGameObject(new AniPlayer());
	
	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

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

	scrollOffset += dt * aniPlayer->GetSpeed();
	
	background1.setPosition(-scrollOffset, 0);
	background2.setPosition(-scrollOffset + backgroundWidth, 0);

	if (scrollOffset >= backgroundWidth)
	{
		scrollOffset -= backgroundWidth;
	}
	
	//-------------------------------------------------nextScene

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	window.draw(background1);
	window.draw(background2);	
	
	Scene::Draw(window);
}