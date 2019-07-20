#include "FrameworkPCH.h"

Framework::Framework()
{
	m_CurrentWindowWidth = -1;
	m_CurrentWindowHeight = -1;
}

void Framework::Init(int width, int height)
{
    m_CurrentWindowWidth = width;
    m_CurrentWindowHeight = height;
}
