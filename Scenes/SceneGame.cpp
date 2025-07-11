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

	backgroundTexture.loadFromFile("img/Objectimg/map1img/bg1.png");
	background1.setTexture(backgroundTexture);
	background2.setTexture(backgroundTexture);
	backgroundWidth = backgroundTexture.getSize().x;

	//-------------------------------------------------cookieSet

	cookieTexture.loadFromFile("img/cookieimg/cookie1/player_attack.png");
	cookieOrigin.setTexture(cookieTexture);
	cookieOrigin.setPosition({ 0,0 });

	cookie = new Cookie("braveCookie");

	AddGameObject(cookie);
	//cookie->sortingLayer = SortingLayers::Default;
	//cookie->sortingOrder = 0;
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
	scrollSpeed = 100.0f;
	scrollOffset += dt * scrollSpeed;
	
	background1.setPosition(-scrollOffset, 0);
	background2.setPosition(-scrollOffset + backgroundWidth, 0);
	

	if (scrollOffset >= backgroundWidth)
	{
		scrollOffset -= backgroundWidth;
	}
	std::cout<< offsetX <<","<< scrollOffset + backgroundWidth << std::endl;

	////test

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
	window.draw(cookieOrigin);
}