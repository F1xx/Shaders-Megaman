#ifndef __FloatingScene_H__
#define __FloatingScene_H__

#include "Scene.h"

class FloatingScene : public Scene
{
public:

protected:

public:
    FloatingScene(Game* pGame, ResourceManager* pResources);
    virtual ~FloatingScene();

    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();
};

#endif //__Scene_H__
