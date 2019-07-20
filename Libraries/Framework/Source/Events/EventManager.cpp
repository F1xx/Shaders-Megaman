#include "FrameworkPCH.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
    while( m_Events.empty() == false )
    {
        delete m_Events.front();
        m_Events.pop();
    }
}

void EventManager::QueueEvent(Event* pEvent)
{
    assert( pEvent != 0 );

    m_Events.push( pEvent );
}

void EventManager::DispatchEvents(GameCore* pGameCore)
{
    while( m_Events.empty() == false )
    {
        Event* pEvent = m_Events.front();

        pGameCore->OnEvent( pEvent );
        m_Events.pop();

        delete pEvent;
    }
}
