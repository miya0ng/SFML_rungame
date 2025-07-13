#pragma once
#include "GameObject.h"
class Obstacle :
    public GameObject
{
public:
    
    Obstacle(const std::string& name)
		: GameObject(name) {
	}
    virtual void SpawnJelly(std::vector<GameObject*>& jellyList) {}
};