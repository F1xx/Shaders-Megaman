#include "GamePCH.h"
#include "PoolTestScene.h"

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

PoolTestScene::PoolTestScene(Game* pGame, ResourceManager* pResources) :
	Scene(pGame, pResources)
{
	vec3 campos = m_Camera->GetPosition();
	campos.z -= 10;
	campos.y -= 3;
	m_Camera->SetPosition(campos);
	m_Camera->SetLookAtPosition(vec3(0.0f, 2.0f, 0.0f));
}

PoolTestScene::~PoolTestScene()
{
}

void PoolTestScene::LoadContent()
{
	Scene::LoadContent();

	//make the player
	Player* player = new Player(this, "Player", Transform(vec3(0, 5, 0), vec3(0), vec3(1)), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Cube"));
	player->SetPlayerController(m_pGame->GetController(0));
	player->CreateBody(false);
	player->AddBox(vec2(0.5f, 0.5f));
	player->GetBody()->SetGravityScale(0.0f);
	m_pGameObjects.push_back(player);

	for (int i = 0; i < 50; i++)
	{
		GameObject* balls = new GameObject(this, "Ball" + std::to_string(i), Transform(vec3(0, 1, 0), vec3(0), vec3(0.2f)), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Meteor"));
		balls->CreateBody(false);
		balls->AddBox(vec2(0.2f, 0.2f));
		m_pGameObjects.push_back(balls);
	}

	//the floor basically
	GameObject* ground = new GameObject(this, "Ground", Transform(vec3(0, 0, 0), vec3(0), vec3(1)), m_pResources->GetMesh("Plane"), m_pResources->GetMaterial("Cube"));
	ground->CreateBody(true);
	ground->AddBox(vec2(10.0f, 0.01f));
	m_pGameObjects.push_back(ground);
}

void PoolTestScene::OnEvent(Event* pEvent)
{
	Scene::OnEvent(pEvent);
}

void PoolTestScene::Update(float deltatime)
{
	Scene::Update(deltatime);
}

void PoolTestScene::Draw()
{
	Scene::Draw();
}
