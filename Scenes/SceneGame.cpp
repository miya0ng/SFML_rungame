#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	go->SetString("Start");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

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

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}