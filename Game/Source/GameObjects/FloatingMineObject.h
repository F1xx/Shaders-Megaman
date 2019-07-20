#ifndef __FloatingMineObject_H__
#define __FloatingMineObject_H__

#include "FloatingObject.h"

class FloatingMineObject : public FloatingObject
{
public:
    bool m_AttachedToPlayer;

public:
    FloatingMineObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial);
    virtual ~FloatingMineObject();

    virtual void Update(float deltatime);
};

#endif //__FloatingMineObject_H__
