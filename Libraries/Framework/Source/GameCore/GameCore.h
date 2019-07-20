#ifndef __GameCore_H__
#define __GameCore_H__

class Framework;
class Event;
class EventManager;

class GameCore
{
protected:
    Framework* m_pFramework;
    EventManager* m_pEventManager;

public:
    GameCore(Framework* pFramework, EventManager* pEventManager);
    virtual ~GameCore();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) = 0;
    virtual void LoadContent() = 0;

    virtual void OnEvent(Event* pEvent) = 0;
    virtual void Update(float deltatime) = 0;
    virtual void Draw() = 0;

    Framework* GetFramework() { return m_pFramework; }
    EventManager* GetEventManager() { return m_pEventManager; }
};

#endif //__GameCore_H__
