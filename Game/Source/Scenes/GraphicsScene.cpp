#include "GamePCH.h"
#include "GraphicsScene.h"

#include "../Game/Game.h"
#include "Game/ResourceManager.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "../Physics/PhysicsWorld.h"

#include "Mesh/SpriteSheet.h"
#include "GameObjects/Camera.h"

GraphicsScene::GraphicsScene(Game * pGame, ResourceManager * pResources) :
	Scene(pGame, pResources)
{
	m_Camera->SetPosition(vec3(0.0f, 0.0f, -10.0f));
	m_Camera->SetLookAtPosition(vec3(0.0f, 0.0f, 0.0f));
	m_Wireframe = true;
}

GraphicsScene::~GraphicsScene()
{
}

void GraphicsScene::LoadContent()
{
	Scene::LoadContent();

	Player* player = new Player(this, "Player", Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)), m_pResources->GetMesh("Table"), m_pResources->GetMaterial("Cube"));
	player->SetPlayerController(m_pGame->GetController(0));
	//player->CreateBody(b2_dynamicBody);

	m_pGameObjects.push_back(player);
}

void GraphicsScene::OnEvent(Event* pEvent)
{
	Scene::OnEvent(pEvent);
}

void GraphicsScene::Update(float deltatime)
{
	Scene::Update(deltatime);
	//m_Camera->SetLookAtPosition(m_pGameObjects[0]);
}

void GraphicsScene::Draw()
{
	Scene::Draw();
}
