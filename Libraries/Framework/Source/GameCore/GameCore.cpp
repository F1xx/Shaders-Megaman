#include "FrameworkPCH.h"

GameCore::GameCore(Framework* pFramework, EventManager* pEventManager)
{
    m_pFramework = pFramework;
    m_pEventManager = pEventManager;
}

GameCore::~GameCore()
{
    delete m_pEventManager;
}
