#include "GamePCH.h"

#include "FloatingScene.h"
#include "../GameObjects/FloatingMineObject.h"
#include "../GameObjects/FloatingPlayerObject.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Scene.h"
#include "../GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"

#include <string>

FloatingScene::FloatingScene(Game* pGame, ResourceManager* pResources)
: Scene( pGame, pResources )
{
	m_Camera->SetRange(300.0f);
}

FloatingScene::~FloatingScene()
{
}

void FloatingScene::LoadContent()
{
    Scene::LoadContent();
    
    // Load shaders specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddShader( "FloatingWater", new ShaderProgram( "Data/Shaders/Water2.vert", "Data/Shaders/Water2.frag" ) );
    }

    // Create meshes specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddMesh( "FloatingSprite", new Mesh() )->CreateBox( vec2(1,1), vec2(0,0) );
		m_pResources->AddMesh("FloatingWater", new Mesh())->CreatePlane(vec2(300, 300), ivec2(300, 300));// , vec2(150, 150) );
    }

    // Load textures specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddTexture( "FloatingWater",   new Texture( "Data/Textures/Water.png" ) );
        m_pResources->AddTexture( "FloatingMeteor",  new Texture( "Data/Textures/Meteor.png" ) );
    }

    // Create materials specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddMaterial( "FloatingWater", new Material( m_pResources->GetShader( "FloatingWater" ), m_pResources->GetTexture( "FloatingWater" ) ) );
        m_pResources->AddMaterial( "FloatingMeteor", new Material( m_pResources->GetShader( "TextureShader" ), m_pResources->GetTexture( "FloatingMeteor" ) ) );
    }
    
    // Create some game objects.
    {
         //Water
        GameObject* pObject = new GameObject( this, "Water", Transform(vec3(0), vec3(0), vec3(1)), m_pResources->GetMesh( "FloatingWater" ), m_pResources->GetMaterial( "FloatingWater" ) );
        AddGameObject( pObject );

        // Player
        FloatingPlayerObject* pPlayer = new FloatingPlayerObject( this, "Player", Transform(vec3(0), vec3(0), vec3(1)), m_pResources->GetMesh( "FloatingSprite" ), m_pResources->GetMaterial( "Megaman" ) );
        AddGameObject( pPlayer );
        pPlayer->SetController( m_pGame->GetController( 0 ) );

        // Mines
        for( int i=0; i<20; i++ )
        {
            std::string minename = "Mine" + std::to_string( i );
            vec3 pos( (float)sin((float)i)*10.0f, 0.0f, 3.0f + i*3.0f );
            GameObject* pObject = new FloatingMineObject( this, minename, Transform(pos, vec3(0,0,0), vec3(1)), m_pResources->GetMesh( "FloatingSprite" ), m_pResources->GetMaterial( "FloatingMeteor" ) );

            AddGameObject( pObject );
        }

        // DONE TODO_Floating: Create a new camera class that will follow the player with an offset and look at the player. 
        // Set the camera to follow the player.
		m_Camera->SetLookAtTarget(pPlayer, Vector3(0.0f, 10.0f, -20.0f));
	}
}

void FloatingScene::Update(float deltatime)
{
    Scene::Update( deltatime );
}

void FloatingScene::Draw()
{
    Scene::Draw();
}
