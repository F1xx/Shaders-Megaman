#ifndef __EventManager_H__
#define __EventManager_H__

class EventManager
{
protected:
    std::queue<Event*> m_Events;

public:
    EventManager();
    virtual ~EventManager();

    virtual void QueueEvent(Event* pEvent);
    virtual void DispatchEvents(GameCore* pGameCore);
};

#endif //__EventManager_H__
