#include "stdafx.h"
#include "SceneReady.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneReady::SceneReady()
	: Scene(SceneIds::Ready)
{
}

void SceneReady::Init()
{
	texIds.push_back("graphics/ready.png");
	SpriteGo* readySprite = new SpriteGo("graphics/ready.png");
	TEXTURE_MGR.Load("graphics/ready.png");
	readySprite->GetSprite().setTexture(
		TEXTURE_MGR.Get("graphics/ready.png")
	);
	AddGameObject(readySprite);

	Scene::Init();
}

void SceneReady::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

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