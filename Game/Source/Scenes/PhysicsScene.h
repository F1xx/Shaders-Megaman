#pragma once
#include "Scenes/Scene.h"
class DebugDraw;

class PhysicsScene : public Scene
{
public:
	PhysicsScene(Game* pGame, ResourceManager* pResources);
	virtual ~PhysicsScene();

	virtual void LoadContent() override;
	virtual void OnEvent(Event* pEvent) override;
	virtual void Update(float deltatime) override;
	virtual void Draw() override;
};