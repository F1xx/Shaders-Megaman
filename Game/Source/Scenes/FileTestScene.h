#pragma once
#include "Scenes/Scene.h"
class DebugDraw;

class FileTestScene : public Scene
{
public:
	FileTestScene(Game* pGame, ResourceManager* pResources);
	virtual ~FileTestScene();

	virtual void LoadContent() override;
	virtual void OnEvent(Event* pEvent) override;
	virtual void Update(float deltatime) override;
	virtual void Draw() override;
};
