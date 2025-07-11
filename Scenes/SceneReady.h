#pragma once
#include "Scene.h"
class SceneReady :
    public Scene
{
protected:

public:
	SceneReady();
	~SceneReady() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

