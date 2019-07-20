#include "GamePCH.h"
#include "FloatingObject.h"

FloatingObject::FloatingObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, transform, pMesh, pMaterial )
{
}

FloatingObject::~FloatingObject()
{
}

void FloatingObject::Update(float deltatime)
{
    GameObject::Update( deltatime );
    //TODO_Floating: Make the objects float on the water.
	float time = (float)GetSystemTimeSinceGameStart();

	m_Position.y -= yoff;
	yoff = 0.4f;

	yoff += sinf(m_Position.x / 5.0f + time) * 1.0f;
	yoff -= sinf(m_Position.z / 40.0f + time) * 2.0f;

	m_Position.y += yoff;
}
