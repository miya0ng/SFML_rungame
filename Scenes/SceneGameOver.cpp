#include "stdafx.h"
#include "SceneGameOver.h"
#include"TextGo.h"

SceneGameOver::SceneGameOver()
	: Scene(SceneIds::GameOver)
{
}

void SceneGameOver::Init()
{
	fontIds.push_back("fonts/CookieRun Bold.ttf");

	TextGo* go = new TextGo("fonts/CookieRun Bold.ttf", "GameOver");
	go->SetString("GAME OVER");
	go->SetCharacterSize(120);
	go->SetPosition({ FRAMEWORK.GetWindowBounds().width * 0.5f + 100.f, FRAMEWORK.GetWindowBounds().height });
	go->SetOrigin(Origins::MC);
	go->SetFillColor(sf::Color::White);

	AddGameObject(go);
	Scene::Init();
}

void SceneGameOver::Enter()
{
	soundIds.push_back("bgm/end.ogg");
	SOUNDBUFFER_MGR.Load("bgm/end.ogg");
	SOUND_MGR.PlayBgm("bgm/end.ogg", false);
	Scene::Enter();
}

void SceneGameOver::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Ready);
	}
}