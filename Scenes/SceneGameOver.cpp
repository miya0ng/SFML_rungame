#include "stdafx.h"
#include "SceneGameOver.h"
#include"TextGo.h"

SceneGameOver::SceneGameOver()
	: Scene(SceneIds::GameOver)
{
}

void SceneGameOver::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "GameOver");
	go->SetString("GameOver");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);


	Scene::Init();
}

void SceneGameOver::Enter()
{
	Scene::Enter();
}

void SceneGameOver::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}