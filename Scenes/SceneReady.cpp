#include "stdafx.h"
#include "SceneReady.h"
#include "TextGo.h"

SceneReady::SceneReady()
	: Scene(SceneIds::Ready)
{
}

void SceneReady::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Ready");
	go->SetString("Ready");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	Scene::Init();
}

void SceneReady::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();
}

void SceneReady::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}