#include "GamePCH.h"

#include "Game/Game.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Framework* pFramework = new Framework();

    pFramework->Init( SCREEN_WIDTH, SCREEN_HEIGHT );

    GameCore* pGame = new Game( pFramework );

    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;

#if _DEBUG
    MyMemory_ValidateAllocations( true );
#endif
}
