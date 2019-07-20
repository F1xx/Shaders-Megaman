#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;
class ResourceManager;
class PhysicsWorld;
class Camera;

#include "../Game/Pool.h"

class Scene
{
protected:
    Game* m_pGame;
    ResourceManager* m_pResources;

    std::vector<GameObject*> m_pGameObjects;

	PhysicsWorld* m_pPhysicsWorld;

	Pool<GameObject*>* m_pCubePool;

	bool m_Wireframe;
	bool m_DebugDraw;

	Camera* m_Camera;

public:
    Scene(Game* pGame, ResourceManager* pResources);
    virtual ~Scene();

    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

	void LoadFromSceneFile(std::string filename);

	void AddGameObject(GameObject* pObject);
	bool RemoveGameObject(GameObject* pObject);
	GameObject* GetGameObjectByName(std::string name);

    Game* GetGame() { return m_pGame; }
    ResourceManager* GetResourceManager() { return m_pResources; }
	PhysicsWorld* GetPhysicsWorld() { return m_pPhysicsWorld; }
	b2World* Getb2World();
};

#endif //__Scene_H__
