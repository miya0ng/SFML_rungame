#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

