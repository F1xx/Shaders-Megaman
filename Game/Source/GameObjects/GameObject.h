#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Mesh;
class Scene;
class Material;
class Camera;
class ResourceManager;
#include "Transformable.h"

#include "../Game/PooledObject.h"

class GameObject : public Transformable
{
protected:
    Game* m_pGame;

	Scene* m_pScene;
	b2Body* m_pBody;

    Mesh* m_pMesh;
	Material* m_pMaterial;

	std::string m_Name;

public:
	GameObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial);

    virtual ~GameObject();

    virtual void OnEvent(Event* pEvent) {}
	virtual void Update(float deltatime);
	virtual void Draw(Camera* cam);

	Mesh* GetMesh() { return m_pMesh; }
	Material* GetMaterial() { return m_pMaterial; }
	std::string GetName() { return m_Name; }

    // Setters
    void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; }
    void SetMaterial(Material* pMat) { m_pMaterial = pMat;}
	b2Body* GetBody();

	virtual void CreateBody(bool isdynamic);
	virtual void CreateRevolute(bool isMotorEnabled, float motorSpeed, float motorTorque);
	void AddBox(vec2 size, float32 density = 1.0f, b2Vec2 offset = b2Vec2(0.0f, 0.0f), bool isSensor = false, float32 friction = 0.7f, float32 restitution = 0.0f);
	void AddCircle(float32 radius, b2Vec2 offset = b2Vec2(0.0f, 0.0f), float32 density = 1.0f, bool isSensor = false, float32 friction = 0.7f, float32 restitution = 0.0f);
	void AddEdge();

	virtual void BeginContact(b2Fixture* fix, vec2 pos, vec2 normal);
	virtual void EndContact(GameObject* pobj);

	virtual void LoadFromcJSON(cJSON* obj, ResourceManager* manager);
	virtual void HandleJoints(cJSON* obj);
};

#endif //__GameObject_H__
