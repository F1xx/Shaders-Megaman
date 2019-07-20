#include "GamePCH.h"
#include "PhysicsScene.h"

#include "../Game/Game.h"
#include "Game/ResourceManager.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "../Physics/PhysicsWorld.h"
#include "Mesh/SpriteSheet.h"

#include "DebugDraw.h"
#include "GameObjects/Camera.h"

PhysicsScene::PhysicsScene(Game* pGame, ResourceManager* pResources) :
	Scene(pGame, pResources)
{
	m_Camera->SetPosition(vec3(0.0f, 10.0f, -10.0f));
	m_Camera->SetLookAtPosition(vec3(0.0f, 0.0f, 0.0f));
	m_Wireframe = true;
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::LoadContent()
{
	Scene::LoadContent();

	//make the player
	Player* player = new Player(this, "Player", Transform(vec3(0,0,0), vec3(0), vec3(1)), m_pResources->GetMesh("Plane"), m_pResources->GetMaterial("Water"));
	player->SetPlayerController(m_pGame->GetController(0));
	m_pGameObjects.push_back(player);

	//m_Camera->SetLookAtPosition(player);
}

void PhysicsScene::OnEvent(Event* pEvent)
{
	Scene::OnEvent(pEvent);
}

void PhysicsScene::Update(float deltatime)
{
	Scene::Update(deltatime);
}

void PhysicsScene::Draw()
{
	Scene::Draw();
}
