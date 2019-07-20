#include "GamePCH.h"

#include "FloatingMineObject.h"

FloatingMineObject::FloatingMineObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial)
: FloatingObject( pScene, name, transform, pMesh, pMaterial )
{
    m_AttachedToPlayer = false;
}

FloatingMineObject::~FloatingMineObject()
{
}

void FloatingMineObject::Update(float deltatime)
{
    FloatingObject::Update( deltatime );
}
