#pragma once
#include "Scenes/Scene.h"

class GraphicsScene : public Scene
{
public:
	GraphicsScene(Game* pGame, ResourceManager* pResources);
	virtual ~GraphicsScene();

	virtual void LoadContent() override;
	virtual void OnEvent(Event* pEvent) override;
	virtual void Update(float deltatime) override;
	virtual void Draw() override;
};