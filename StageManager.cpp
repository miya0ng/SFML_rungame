#include "stdafx.h"
#include "StageManager.h"

void StageManager::Init()
{
    
}

Platform* StageManager::SpawnTile(TileType type)
{
    float startX = activeTiles.empty()
        ? 1000.f                                  // 첫 타일이면 0
        : activeTiles.back()->GetPosition().x  // 마지막 타일 x
        + intervalX;                         // 그 오른쪽에 붙이기

    // 2️⃣ 풀에서 꺼내거나 새로 생성
    Platform* tile = nullptr;
    if (!pooledTiles.empty())
    {
        tile = pooledTiles.back();
        pooledTiles.pop_back();
        tile->SetActive(true);
    }
    else
    {
        tile = new Platform();
        tile->SetScale({ 1.f, 1.f });
        activeTiles.push_back(tile);
    }
    // 3️⃣ 공통 초기화
    tile->Init();
    tile->SetType(type);
    float tileWidth = tile->GetGlobalBounds().width;
    for (auto it : activeTiles)
    {
        it->SetPosition({ startX, 0 });
        startX += tileWidth;
    }
    return tile;
}

void StageManager::Update(float dt, float playerSpeed)
{
    for (auto it = activeTiles.begin(); it != activeTiles.end();)
    {
        if ((*it)->GetPosition().x < basicTile.getSize().x)
        {
            (*it)->SetActive(false);
            pooledTiles.push_back(*it);
            it = activeTiles.erase(it);
        }
        else
        {
            sf::Vector2f pos = (*it)->GetPosition();
            pos.x -= 100.f * dt;
            (*it)->SetPosition(pos);
            (*it)->Update(dt);
           
			std::cout << (*it)->GetPosition().x << std::endl;
            ++it;
        }
    }
}

void StageManager::Draw(sf::RenderWindow& win)
{
    for (auto* t : activeTiles)
        t->Draw(win);
}