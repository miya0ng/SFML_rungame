#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"
#include "Cookie.h"
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
	AddGameObject(go);

	cookie = (Cookie*)AddGameObject(new Cookie("brave cookie"));
	cookie->sortingLayer = SortingLayers::Foreground;
	cookie->sortingOrder = 5;
	cookie->SetPosition({ 500.f, 500.f });
	cookie->SetScale({ 1.f, 1.f });


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
void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
