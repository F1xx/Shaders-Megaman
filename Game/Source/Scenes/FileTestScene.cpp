#include "GamePCH.h"
#include "FileTestScene.h"

#include "../Game/Game.h"
#include "Game/ResourceManager.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "../Physics/PhysicsWorld.h"
#include "Mesh/SpriteSheet.h"
#include "GameObjects/Camera.h"

#include "DebugDraw.h"
#include <string>

FileTestScene::FileTestScene(Game* pGame, ResourceManager* pResources) :
	Scene(pGame, pResources)
{
	m_Camera->SetPosition(vec3(0,0,-15));
	m_Camera->SetLookAtPosition(vec3(0.0f, 0.0f, 0.0f));
	m_Camera->SetRange(200.0f);
}

FileTestScene::~FileTestScene()
{
}

void FileTestScene::LoadContent()
{
	Scene::LoadContent();

	//LoadFromSceneFile("Data/Scenes/Simple.box2dscene");
	//LoadFromSceneFile("Data/Scenes/Slopes.box2dscene");
	LoadFromSceneFile("Data/Scenes/Joints.box2dscene");
}

void FileTestScene::OnEvent(Event* pEvent)
{
	Scene::OnEvent(pEvent);
}

void FileTestScene::Update(float deltatime)
{
	Scene::Update(deltatime);
}

void FileTestScene::Draw()
{
	Scene::Draw();
}
