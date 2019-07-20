#pragma once
#include "Scenes/Scene.h"
class DebugDraw;

class PoolTestScene : public Scene
{
public:
	PoolTestScene(Game* pGame, ResourceManager* pResources);
	virtual ~PoolTestScene();

	virtual void LoadContent() override;
	virtual void OnEvent(Event* pEvent) override;
	virtual void Update(float deltatime) override;
	virtual void Draw() override;
};
