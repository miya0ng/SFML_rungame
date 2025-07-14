#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "AniPlayer.h"
#include "Background.h"
#include "StageManager.h"
#include <cmath>

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{

}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	//texIds.push_back("img/Objectimg/map1img/bg1.png");

	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/player_origin.png");
	texIds.push_back("graphics/player_jump.png");
	texIds.push_back("graphics/player_slide.png");
	//texIds.push_back("img/Objectimg/map1img/platform1.png");

	std::cout << "sceneGame init()" << std::endl;
	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/cookierun.csv");
	ANI_CLIP_MGR.Load("animations/cookiejump.csv");
	ANI_CLIP_MGR.Load("animations/cookieslide.csv");
	
	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf", "Game");
	go->SetString("Start");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	AddGameObject(go);

	//-------------------------------------------------cookieSet
	bg = new Background();	
	aniPlayer=(AniPlayer*)AddGameObject(new AniPlayer());
	bg->SetPlayer(aniPlayer);	
	bg->Init();

	stageManager = new StageManager();
	stageManager->Init();
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
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	//if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	//{
	//	sf::Vector2i mouse = InputMgr::GetMousePosition();
	//	std::cout << mouse.x << ", " << mouse.y << std::endl;
	//}
	//-------------------------------------------------backgroundScroll

	bg->Update(dt);

	//-------------------------------------------------stageManagerUpdate

	stageManager->SpawnTile(TileType::Ground);
	//stageManager->Update(dt, scrollSpeed);

	//--------------------------------------------------aniPlayerUpdate
	
	//sf::Image maskImage;	
	//sf::Vector2f characterPos;
	//sf::Vector2u maskSize;
	//void Player::Init()
	//{
	//	maskImage.loadFromFile("graphics/stage1/back_Hit_Mask.png");
	//}
	
	// player Update
	// player Scale = { 4.f, 3.f }
	// mask size { 480, 360 };

	//scaleX = 1.f / character.getScale().x; // 0.25
	//scaleY = 1.f / character.getScale().y; // 0.333

	//// 월드좌표 가져오기
	//characterPos = character.getPosition();

	//// Vector2u는 부호가 없는 정수 Vector2u == Vector2<unsigned int>
	//sf::Vector2u maskCoord(characterPos.x * scaleX, characterPos.y * scaleY);

	//// 플레이어의 현재 좌표에 픽셀을 저장
	//sf::Color pixelColor = maskImage.getPixel(maskCoord.x, maskCoord.y);

	//// 픽셀 충돌검사
	//if (pixelColor == sf::Color::Blue)
	//{
	//	std::cout << "벽 충돌!" << std::endl;
	//}
	//if (pixelColor == sf::Color::Black)
	//{
	//	std::cout << "착지 충돌!" << std::endl;
	//}

	//-------------------------------------------------nextScene

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	bg->Draw(window);
	stageManager->Draw(window);
	Scene::Draw(window);
}