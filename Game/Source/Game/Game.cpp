#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Mesh/SpriteSheet.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "ResourceManager.h"
#include "Scenes/Scene.h"
#include "Scenes/GraphicsScene.h"
#include "Scenes/PhysicsScene.h"
#include "Scenes/PoolTestScene.h"
#include "Scenes/FloatingScene.h"
#include "Scenes/FileTestScene.h"
#include "ImGuiManager.h"

Game::Game(Framework* pFramework)
: GameCore( pFramework, new EventManager() )
{
	m_pResourceManager = nullptr;

	m_pCurrentScene = nullptr;

    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = nullptr;
    }

    m_pPlayer = nullptr;
}

Game::~Game()
{
    delete m_pPlayer;

    for( int i=0; i<4; i++ )
    {
        delete m_pControllers[i];
    }

	delete m_pResourceManager;
	delete m_pImGuiManager;

	for (auto object : m_pScenes)
		delete object.second;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport( 0, 0, width, height );
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval( 1 );
#endif

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	m_pResourceManager = new ResourceManager();

	//MESHES
	{
		//Add things to resource manager.
		m_pResourceManager->AddMesh("Cube", new Mesh());
		m_pResourceManager->GetMesh("Cube")->CreateCube(vec3(1, 1, 1), vec3(0, 0, 0));

		m_pResourceManager->AddMesh("Box", new Mesh());
		m_pResourceManager->GetMesh("Box")->CreateBox(vec2(1.0f, 1.0f), vec2(0.0f, 0.0f));

		m_pResourceManager->AddMesh("Plane", new Mesh());
		m_pResourceManager->GetMesh("Plane")->CreatePlane(vec2(10.0f, 10.0f), ivec2(60, 30));

		m_pResourceManager->AddMesh("Obj", new Mesh());
		m_pResourceManager->GetMesh("Obj")->GenerateOBJ("Data/OBJ/cube.obj");

		m_pResourceManager->AddMesh("Sphere", new Mesh());
		m_pResourceManager->GetMesh("Sphere")->GenerateOBJ("Data/OBJ/sphere.obj");

		m_pResourceManager->AddMesh("Table", new Mesh());
		m_pResourceManager->GetMesh("Table")->GenerateOBJ("Data/OBJ/Table.obj", 0.01f);
	}

    // Create our shaders.
	{
		m_pResourceManager->AddShader("TextureShader", new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag"));
		m_pResourceManager->AddShader("WaterShader", new ShaderProgram("Data/Shaders/Water.vert", "Data/Shaders/Water.frag"));
		m_pResourceManager->AddShader("DebugShader", new ShaderProgram("Data/Shaders/Debug.vert", "Data/Shaders/Debug.frag"));
	}

    // Load some textures.
	{
		m_pResourceManager->AddTexture("Megaman", new Texture("Data/Textures/Megaman.png"));
		m_pResourceManager->AddTexture("Dice", new Texture("Data/Textures/Dice.png"));
		m_pResourceManager->AddTexture("Meteor", new Texture("Data/Textures/Meteor.png"));
		m_pResourceManager->AddTexture("Water", new Texture("Data/Textures/Water.png"));
		m_pResourceManager->AddTexture("Ground", new Texture("Data/Textures/Ground.png"));
	}

	//Spritesheets
	{
		m_pResourceManager->AddSpriteSheet("Die", new SpriteSheet("DataSource/Dice", "Die1.png"));
	}

	{
		m_pResourceManager->AddMaterial("Cube",    new Material(m_pResourceManager->GetShader("TextureShader"), m_pResourceManager->GetTexture("Dice")));
		m_pResourceManager->AddMaterial("Meteor",  new Material(m_pResourceManager->GetShader("TextureShader"), m_pResourceManager->GetTexture("Meteor")));
		m_pResourceManager->AddMaterial("Megaman", new Material(m_pResourceManager->GetShader("TextureShader"), m_pResourceManager->GetTexture("Megaman")));
		m_pResourceManager->AddMaterial("Ground",  new Material(m_pResourceManager->GetShader("TextureShader"), m_pResourceManager->GetTexture("Ground")));

		m_pResourceManager->AddMaterial("Water",   new Material(m_pResourceManager->GetShader("WaterShader"), m_pResourceManager->GetTexture("Water")));

		m_pResourceManager->AddMaterial("Debug",   new Material(m_pResourceManager->GetShader("DebugShader"), m_pResourceManager->GetTexture("Dice")));
	}

    // Create our controllers.
    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = new PlayerController();
    }

	//Scenes
	m_pScenes["Graphics"] = new GraphicsScene(this, m_pResourceManager);
	m_pScenes["Physics"] = new PhysicsScene(this, m_pResourceManager);
	m_pScenes["PoolTest"] = new PoolTestScene(this, m_pResourceManager);
	m_pScenes["Floatyboi"] = new FloatingScene(this, m_pResourceManager);
	m_pScenes["FileTestScene"] = new FileTestScene(this, m_pResourceManager);

	m_pScenes["Graphics"]->LoadContent();
	m_pScenes["Physics"]->LoadContent();
	m_pScenes["PoolTest"]->LoadContent();
	m_pScenes["Floatyboi"]->LoadContent();
	m_pScenes["FileTestScene"]->LoadContent();

	m_pCurrentScene = m_pScenes["FileTestScene"];

	m_pImGuiManager = new ImGuiManager();
	m_pImGuiManager->Init();

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
	m_pControllers[0]->OnEvent(pEvent);

	m_pImGuiManager->OnEvent(pEvent);

	m_pCurrentScene->OnEvent(pEvent);

#if WIN32
	// Enable/Disable V-Sync with F1 and F2.
	if (pEvent->GetEventType() == EventType_Input)
	{
		InputEvent* pInput = (InputEvent*)pEvent;

		// Enable V-Sync.
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F1)
			wglSwapInterval(1);

		// Disable V-Sync.
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F2)
			wglSwapInterval(0);

		// Scene 1.
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 49)
			m_pCurrentScene = m_pScenes["Floatyboi"];
	
		// Scene 2.
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 50)
			m_pCurrentScene = m_pScenes["Physics"];

		// Scene 3.
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 51)
			m_pCurrentScene = m_pScenes["PoolTest"];

		//Scene 4
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 52)
			m_pCurrentScene = m_pScenes["Graphics"];

		//Scene 5
		if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 53)
			m_pCurrentScene = m_pScenes["FileTestScene"];
	}
#endif //WIN32
}

void Game::Update(float deltatime)
{
	if (deltatime > 0.1f)
	{
		deltatime = 0.1f;
	}
	m_pImGuiManager->StartFrame((float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltatime);

	m_pCurrentScene->Update(deltatime);
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // (red, green, blue, alpha) - dark blue.
#if WIN32
    glClearDepth( 1 ); // 1 is maximum depth.
#endif
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_pCurrentScene->Draw();

	m_pImGuiManager->EndFrame();

    CheckForGLErrors();
}
