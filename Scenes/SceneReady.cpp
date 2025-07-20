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
	SOUNDBUFFER_MGR.Load("bgm/start.ogg");
	soundIds.push_back("bgm/lobby.wav");
	soundIds.push_back("bgm/start.ogg");
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
	SOUND_MGR.SetBgmVolume(50.f);
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
	
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		startSfx = SOUND_MGR.PlaySsfx("bgm/start.ogg", false);
		isButtonPressed = true;
		//SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (isButtonPressed)
	{
		//isButtonPressed = false;
		
		bool finished =
			(startSfx == nullptr) ||
			(startSfx->getStatus() == sf::Sound::Stopped);

		if (finished)
			SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}