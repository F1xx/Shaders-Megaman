#ifndef __FloatingObject_H__
#define __FloatingObject_H__

#include "GameObject.h"

class FloatingObject : public GameObject
{
public:
	float yoff = 0;
public:
    FloatingObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial);
    virtual ~FloatingObject();

    virtual void Update(float deltatime);
};

#endif //__FloatingObject_H__
