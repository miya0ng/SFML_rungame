#include "stdafx.h"
#include "StageManager.h"

void StageManager::Init()
{
	intervalX = basicTile.getSize().x;
}

Platform* StageManager::SpawnTile(TileType type)
{
	Platform* newTile = nullptr;
	switch (type)
	{
	case TileType::Ground:
		newTile = new Platform();
		break;
		/*  case TileType::Moving:
			  newTile = new MovingPlatform();
			  break;
		  case TileType::Floating:
			  newTile = new Floating();
			  break;
		  */
	default:
		return nullptr;
	}
	activeTiles.push_back(newTile);
	return newTile;
}

void StageManager::Update(float dt, float playerSpeed)
{
	sf::FloatRect rect = tile->GetLocalBounds();
	for (int i = 0; i < 50; i++)
	{
		sf::Vector2f pos = activeTiles[i]->GetPosition();
		pos.x -= playerSpeed * dt;
		activeTiles[i]->SetPosition(pos);
	}
	std::cout << "StageManager::Update called with dt: " << dt << " and playerSpeed: " << playerSpeed << std::endl;
}


void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTiles)
		t->Draw(win);
}