#include "stdafx.h"
#include "StageManager.h"

void StageManager::Init()
{
  
}

Platform* StageManager::SpawnTile(TileType type)
{
    if (!pooledTiles.empty()) {
        tile = pooledTiles.back();
        pooledTiles.pop_back();
        tile->SetActive(true);
    }
    else
    {  
        tile = new Platform();
        activeTiles.push_back(tile);
    }

    tile->Init();
    tile->SetType(type);
    return tile;
}


void StageManager::Update(float dt, float playerSpeed)
{
    for (auto it = activeTiles.begin(); it != activeTiles.end(); ) {
        if ((*it)->GetPosition().x < basicTile.getSize().x) {      // 200px ¿ÞÂÊ ¿©À¯
            (*it)->SetActive(false);
            pooledTiles.push_back(*it);
            it = activeTiles.erase(it);
        }
        else
        {
            (*it)->Update(dt);
            ++it;
        }
    }
    tile->SetPosition({ tilePos.x += 100 * dt, 0 });   
	std::cout << tile->GetPosition().x << std::endl;
}

void StageManager::Draw(sf::RenderWindow& win)
{
    for (auto* t : activeTiles)
        t->Draw(win);
}