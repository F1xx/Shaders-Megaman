#ifndef __FloatingPlayerObject_H__
#define __FloatingPlayerObject_H__

#include "FloatingObject.h"
#include "PlayerController.h"

class FloatingPlayerObject : public FloatingObject
{
protected:
    PlayerController* m_pController;
	std::vector<FloatingMineObject*> AttachedMines;
	float angle = 0;

public:
    FloatingPlayerObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial);
    virtual ~FloatingPlayerObject();

    void SetController(PlayerController* pController);

    virtual void Update(float deltatime);

	float DegreesToRadians(float deg);
};

#endif //__FloatingPlayerObject_H__
