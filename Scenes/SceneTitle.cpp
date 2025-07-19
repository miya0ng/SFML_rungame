#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/intro.png");
	SpriteGo* titleSprite = new SpriteGo("graphics/intro.png");
	TEXTURE_MGR.Load("graphics/intro.png");
	titleSprite->GetSprite().setTexture(
		TEXTURE_MGR.Get("graphics/intro.png")
	);
	AddGameObject(titleSprite);
	Scene::Init();
}

void SceneTitle::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

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
