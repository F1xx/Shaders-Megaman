#pragma once
class b2World;
class ContactListener;
class DebugDraw;
class Camera;
class Material;

class PhysicsWorld
{
public:
	PhysicsWorld();
	virtual ~PhysicsWorld();

	void Init(b2Vec2 gravity);

	b2World* GetWorld() { return m_pWorld; }

	void Update(float deltatime);
	void Draw(Camera* cam, Material* mat);

	b2Body* GetWorldBody() { return m_pWorldBody; }

protected:
	b2World* m_pWorld;
	DebugDraw* m_Debugdraw;
	ContactListener* m_pContactListener;
	b2Body* m_pWorldBody;
	float m_TotalTime;
};