#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "Cookie.h"
#include <cmath>

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{

}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	//texIds.push_back("C:/Users/KGA/Desktop/cookie_run/sfml-project-bin/img/Objectimg/map1img/bg1.png"); 

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	go->SetString("Start");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	AddGameObject(go);

	backgroundTexture.loadFromFile("C:/Users/KGA/Desktop/cookie_run/sfml-project-bin/img/Objectimg/map1img/bg1.png");
	background1.setTexture(backgroundTexture);
	background2.setTexture(backgroundTexture);
	backgroundWidth = backgroundTexture.getSize().x;
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

	//-------------------------------------------------backgroundScroll
	scrollSpeed = 200.0f;
	scrollOffset += dt * scrollSpeed;
	
	float offsetX = -fmod(scrollOffset, backgroundWidth);
	background1.setPosition(offsetX, 0);
	background2.setPosition(background1.getPosition().x +backgroundWidth, background1.getPosition().y);
	
	if (scrollOffset >= backgroundWidth)
	{
		scrollOffset -= backgroundWidth; 
	}

	//-------------------------------------------------cookieSet

	braveCookie.




	//-------------------------------------------------nextScene

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(background1);
	window.draw(background2);
}