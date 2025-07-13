#pragma once
#include "Obstacle.h"
class Spikes :
    public Obstacle
{
public:
    void SpawnJelly(std::vector<GameObject*>& jellyList) override;
};

