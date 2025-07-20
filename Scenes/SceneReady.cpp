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
	SOUNDBUFFER_MGR.Load("bgm/lobby.wav");
	soundIds.push_back("bgm/lobby.wav");
	texIds.push_back("graphics/ready.png");
	SpriteGo* readySprite = new SpriteGo("graphics/ready.png");
	TEXTURE_MGR.Load("graphics/ready.png");
	readySprite->GetSprite().setTexture(
		TEXTURE_MGR.Get("graphics/ready.png")
	);
	AddGameObject(readySprite);
	button.setSize({ 184.f,69.f });
	button.setPosition({ FRAMEWORK.GetWindowBounds().width - 184.f,FRAMEWORK.GetWindowBounds().height - 69.f });
	
	Scene::Init();
}

void SceneReady::Enter()
{
	SOUND_MGR.PlayBgm("bgm/lobby.wav");
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
	sf::RenderWindow& win = FRAMEWORK.GetWindow();
	mouseWorldPos= win.mapPixelToCoords(sf::Mouse::getPosition(win));
	isMouseOver = Utils::PointInTransformBounds(button, button.getLocalBounds(), mouseWorldPos);
		std::cout << mouseWorldPos.x << std::endl;
	if (isMouseOver)
	{
		button.setFillColor(sf::Color::Black);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		else
		{
			button.setFillColor(sf::Color::Transparent);
		}
	}
}