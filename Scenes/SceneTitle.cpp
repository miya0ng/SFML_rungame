#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf","title");
	go->SetString("Title");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	std::cout <<"xÁÂÇ¥:" << go->GetPosition().x << std::endl;
	std::cout << "yÁÂÇ¥:" << go->GetPosition().y << std::endl;

	AddGameObject(go);

	Scene::Init();
}

void SceneTitle::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Ready);
	}
}