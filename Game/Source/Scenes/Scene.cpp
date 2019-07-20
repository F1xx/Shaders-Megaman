#include "GamePCH.h"

#include "../Game/Game.h"
#include "Game/ResourceManager.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "../Physics/PhysicsWorld.h"

#include "Mesh/SpriteSheet.h"
#include "GameObjects/Camera.h"
#include "../SaveLoad.h"

#include <string.h>

Scene::Scene(Game* pGame, ResourceManager* pResources)
{
    m_pGame = pGame;
    m_pResources = pResources;
	m_pPhysicsWorld = new PhysicsWorld();
	m_pPhysicsWorld->Init(b2Vec2(0, -1));
	m_pCubePool = nullptr;
	m_Wireframe = false;
	m_DebugDraw = false;

	m_Camera = new Camera(vec3(0.0f, 5.0f, -5.0f), vec3(5.0f, 5.0f, 0.0f), 100.0f);
	m_Camera->CreateProjectionMatrix();
	m_Camera->CreateViewMatrix();
}

Scene::~Scene()
{
    for( auto pObject: m_pGameObjects )
    {
        delete pObject;
    }

	delete m_pPhysicsWorld;
	delete m_pCubePool;
	delete m_Camera;
}

void Scene::LoadContent()
{
	//m_pCubePool = new Pool<GameObject*>();
	//for (int i = 0; i < 100; i++)
	//{
	//	GameObject* pobj =  new GameObject(this, "PooledObj", Transform(vec3(0,0,0), vec3(0,0,0), vec3(1,1,1)), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Megaman"));
	//	m_pCubePool->AddObjectToPool(pobj);
	//}
}

void Scene::OnEvent(Event* pEvent)
{
	if (pEvent->GetEventType() == EventType_Input)
	{
		InputEvent* pInput = (InputEvent*)pEvent;

		// Spawn
		//if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'N')
		//{
		//	GameObject* pObj = m_pCubePool->GetObjectFromPool();
		//	if (pObj)
		//	{
		//		pObj->SetPosition(vec2((float)(rand() % 5) + 2.5f, (float)(rand() % 5) + 2.5f));
		//		m_pGameObjects.push_back(pObj);
		//	}
		//}

		//// DeSpawn
		//if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'K')
		//{
		//	if (m_pGameObjects.size() > 1)
		//	{
		//		GameObject* pObj = m_pGameObjects.back();
		//		m_pGameObjects.pop_back();
		//		m_pCubePool->ReturnObjectToPool(pObj);
		//	}
		//}

		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'L')
		{
			vec3 campos = m_Camera->GetPosition();
			campos.z -= 1;
			m_Camera->SetPosition(campos);
		}
	}
}

void Scene::Update(float deltatime)
{
	m_Camera->Update(deltatime);

	m_pPhysicsWorld->Update(deltatime);

	for (unsigned int i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects.at(i)->Update(deltatime);
	}

	ImGui::Checkbox("Wireframe", &m_Wireframe);
	if (m_Wireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	ImGui::Checkbox("Debug", &m_DebugDraw);
}

void Scene::Draw()
{
	for (unsigned int i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects.at(i)->Draw(m_Camera);
	}

	if (m_DebugDraw)
	{
		m_pPhysicsWorld->Draw(m_Camera, m_pResources->GetMaterial("Debug"));
	}
}

void Scene::LoadFromSceneFile(std::string filename)
{
	char* contents = LoadCompleteFile(filename.c_str(), nullptr);

	cJSON* jRoot = cJSON_Parse(contents);
	cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

	int numobjects = cJSON_GetArraySize(jGameObjectArray);

	for (int i = 0; i < numobjects; i++)
	{
		cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);

		cJSON* jFlagArray = cJSON_GetObjectItem(jGameObject, "Flags");

		std::string flag;
		if (cJSON_GetArrayItem(jFlagArray, 0) != nullptr)
		{
			flag = cJSON_GetArrayItem(jFlagArray, 0)->valuestring;
		}
		else
		{
			flag = "GameObject";
		}

		//player
		if(flag == "Player")
		{
			Player* player = new Player(this, "Player", Transform(),nullptr, nullptr);
			AddGameObject(player);
			player->SetPlayerController(m_pGame->GetController(0));
			player->LoadFromcJSON(jGameObject, m_pResources);
		}
		else if (flag == "GameObject")
		{
			GameObject* gameobject = new GameObject(this, "Player", Transform(), m_pResources->GetMesh("Box"), nullptr);
			AddGameObject(gameobject);
			gameobject->LoadFromcJSON(jGameObject, m_pResources);
		}

		//add another loop to handlejoints on every object
	}
	cJSON_Delete(jRoot);
	delete[] contents;
}

void Scene::AddGameObject(GameObject * pObject)
{
	m_pGameObjects.push_back(pObject);
}

bool Scene::RemoveGameObject(GameObject * pObject)
{
	auto iteratorForObject = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObject);

	if (iteratorForObject != m_pGameObjects.end())
	{
		m_pGameObjects.erase(iteratorForObject);
		return true;
	}

	return false;
}

GameObject * Scene::GetGameObjectByName(std::string name)
{
	for (auto pObject : m_pGameObjects)
	{
		if (pObject->GetName() == name)
		{
			return pObject;
		}
	}

	return nullptr;
}

b2World* Scene::Getb2World()
{
	return m_pPhysicsWorld->GetWorld();
}
