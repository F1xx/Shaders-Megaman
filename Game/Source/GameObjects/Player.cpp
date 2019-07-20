#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Mesh/SpriteSheet.h"
#include "../Scenes/Scene.h"
#include "../Physics/PhysicsWorld.h"

struct RayCastResultCallback : public b2RayCastCallback
{
	bool m_Hit;
	b2Body* m_pBody;
	RayCastResultCallback()
	{
		m_Hit = false;
		m_pBody = 0;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		m_Hit = true;
		m_pBody = fixture->GetBody();
		return fraction; //store closest body
	}
};

Player::Player(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial)
	: GameObject(pScene, name, transform, pMesh, pMaterial)
	, m_pPlayerController(nullptr)
	, m_Speed(PLAYER_SPEED)
	, m_TurningSpeed(PLAYER_SPEED)
{
}

Player::~Player()
{
}

void Player::Update(float deltatime)
{
    GameObject::Update( deltatime );

    vec3 dir( 0, 0, 0 );

    if( m_pPlayerController )
    {
        if( m_pPlayerController->IsHeld_Up() )
        {
            dir.y = 1;
        }

        if( m_pPlayerController->IsHeld_Down() )
        {
            dir.y = -1;
        }

        if( m_pPlayerController->IsHeld_Left() )
        {
            dir.x = -1;
        }

        if( m_pPlayerController->IsHeld_Right() )
        {
            dir.x = 1;
        }

		if (m_pPlayerController->IsHeld_In())
		{
			dir.z = -1;
		}

		if (m_pPlayerController->IsHeld_Out())
		{
			dir.z = 1;
		}
    }

	if (m_pBody)
	{
		/*float mass = m_pBody->GetMass();
		b2Vec2 currentVel = m_pBody->GetLinearVelocity();
		b2Vec2 TargetVel = b2Vec2(2.0f, 2.0f);
		b2Vec2 VelDiff = TargetVel - currentVel;
		float timestep = 1 / 60.0f;
*/
		//m_pBody->ApplyForceToCenter(mass * VelDiff / timestep);


		b2Vec2 force;
		force.x = dir.x;
		force.y = dir.y;
		force *= m_Speed * deltatime;
		m_pBody->ApplyLinearImpulseToCenter(force, true);
	}
	else
		m_Position += dir * m_Speed * deltatime;

	RayCastResultCallback raycast;
	b2Vec2 point1 = b2Vec2(m_Position.x, m_Position.y);
	b2Vec2 point2 = b2Vec2(m_Position.x, m_Position.y - 6);

	m_pScene->GetPhysicsWorld()->GetWorld()->RayCast(&raycast, point1, point2);

	if (raycast.m_Hit)
	{
		GameObject* obj = (GameObject*)raycast.m_pBody->GetUserData();
		ImGui::Text(obj->GetName().c_str());
	}

}

void Player::Draw(Camera* cam)
{
	GameObject::Draw(cam);

	ImGui::SliderFloat("RotationX", &m_Rotation.x, 0.0f, 360.0f);
	ImGui::SliderFloat("RotationY", &m_Rotation.y, 0.0f, 360.0f);
	ImGui::SliderFloat("RotationZ", &m_Rotation.z, 0.0f, 360.0f);

}