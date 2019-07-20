#ifndef __Game_H__
#define __Game_H__

class Texture;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class ResourceManager;
class Scene;
class ImGuiManager;

class Game : public GameCore
{
protected:

	ResourceManager* m_pResourceManager;

	Scene* m_pCurrentScene;
	//std::vector<Scene*> m_pScenes;

	std::map<std::string, Scene*> m_pScenes;

    PlayerController* m_pControllers[4];

    Player* m_pPlayer;

	ImGuiManager* m_pImGuiManager;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltatime) override;
    virtual void Draw() override;

    PlayerController* GetController(int index) { return m_pControllers[index]; }

	Scene* GetCurrentScene() { return m_pCurrentScene; }
};

#endif //__Game_H__
