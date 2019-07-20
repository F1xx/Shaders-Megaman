#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "../Scenes/Scene.h"
#include "../Game/Game.h"
#include "Mesh/SpriteSheet.h"
#include "GameObject.h"
#include "Mesh/Material.h"
#include "Camera.h"
#include "Transformable.h"
#include "../Game/ResourceManager.h"
#include "Physics/PhysicsWorld.h"

//for use with textures
GameObject::GameObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial)
	: Transformable(transform)
	, m_pScene(pScene)
	, m_Name(name)
	, m_pMesh(pMesh)
	, m_pMaterial(pMaterial)
	, m_pBody(nullptr)
{

}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltatime)
{
	if (m_pBody)
	{
		b2Vec2 pos = m_pBody->GetPosition();
		float angle = m_pBody->GetAngle();

		m_Position.x = pos.x;
		m_Position.y = pos.y;
		m_Rotation.z = -angle / PI * 180.0f;
	}
}

void GameObject::Draw(Camera* cam)
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->SetupAttributes(m_pMaterial->GetShader());

		//worldmatrix
		mat4 matrix;
		matrix.CreateSRT(m_Scale, m_Rotation, m_Position);

		m_pMesh->SetupUniforms(matrix, cam, m_pMaterial);
		m_pMesh->Draw(m_pMaterial->GetShader());
	}
}

b2Body* GameObject::GetBody()
{
	return m_pBody;
}

void GameObject::CreateBody(bool isStatic)
{
	b2BodyDef bodydef;
	bodydef.type = isStatic ? b2_staticBody : b2_dynamicBody;
	bodydef.position.Set(m_Position.x, m_Position.y);
	bodydef.angle = -m_Rotation.z / 180.0f * PI;
	bodydef.userData = this;

	m_pBody = m_pScene->Getb2World()->CreateBody(&bodydef);
}

void GameObject::CreateRevolute(bool isMotorEnabled, float motorSpeed, float motorTorque)
{
	b2RevoluteJointDef jointDef;

	jointDef.Initialize(m_pBody, m_pScene->GetPhysicsWorld()->GetWorldBody(), b2Vec2(m_Position.x, m_Position.y));
	jointDef.enableMotor = isMotorEnabled;
	jointDef.motorSpeed = 0.25f;
	jointDef.maxMotorTorque = 20.0f;
	m_pScene->Getb2World()->CreateJoint(&jointDef);
}

void GameObject::AddBox(vec2 size, float32 density /*= 1.0f*/, b2Vec2 offset /*= b2Vec2(0.0f, 0.0f)*/, bool isSensor /*= false*/, float32 friction /*= 0.2f*/, float32 restitution /*= 0.0f*/)
{
	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y, offset, 0.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.isSensor = isSensor;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	m_pBody->CreateFixture(&fixtureDef);
}

void GameObject::AddCircle(float32 radius, b2Vec2 offset /*= b2Vec2(0.0f, 0.0f)*/, float32 density /*= 1.0f*/, bool isSensor /*= false*/, float32 friction /*= 0.2f*/, float32 restitution /*= 0.0f*/)
{
	b2CircleShape circleShape;
	circleShape.m_p.Set(offset.x, offset.y); // Offset relative to the body
	circleShape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = density;
	fixtureDef.isSensor = isSensor;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	m_pBody->CreateFixture(&fixtureDef);
}

void GameObject::AddEdge()
{
}

void GameObject::BeginContact(b2Fixture* fix, vec2 pos, vec2 normal)
{
}

void GameObject::EndContact(GameObject* pobj)
{

}

void GameObject::LoadFromcJSON(cJSON* obj, ResourceManager* manager)
{
	char* name = new char[50];
	cJSONExt_GetString(obj, "Name", name, 50);
	m_Name = name;
	delete[] name;

	vec3 pos(0);
	cJSONExt_GetFloatArray(obj, "Pos", &pos.x, 3);
	SetPosition(pos);

	vec3 rot(0);
	cJSONExt_GetFloatArray(obj, "Rot", &rot.x, 3);
	SetRotation(rot);

	vec3 scale(0);
	cJSONExt_GetFloatArray(obj, "Scale", &scale.x, 3);
	SetScale(scale);

	cJSON* jComponents = cJSON_GetObjectItem(obj, "Components");
	cJSON* firstComponent = cJSON_GetArrayItem(jComponents, 0);
	cJSON* SecondComponent = cJSON_GetArrayItem(jComponents, 1);

	bool isStatic = false;
	cJSONExt_GetBool(firstComponent, "Static", &isStatic);
	CreateBody(isStatic);
	GetBody()->SetGravityScale(0.8f);

	char* type = new char[50];
	cJSONExt_GetString(firstComponent, "PrimitiveType", type, 50);
	if (strcmp(type, "Box") == 0)
	{
		vec2 size(scale.x * 0.5f, scale.y * 0.5f);

		float32 density = 1.0f;
		cJSONExt_GetFloat(firstComponent, "Density", &density);

		b2Vec2 offset = b2Vec2(0.0f, 0.0f);
		cJSONExt_GetFloatArray(firstComponent, "Offset", &offset.x, 2);

		bool isSensor = false;
		cJSONExt_GetBool(firstComponent, "IsSensor", &isSensor);

		float32 friction = 0.7f;
		cJSONExt_GetFloat(firstComponent, "Friction", &friction);

		float32 restitution = 0.0f;
		cJSONExt_GetFloat(firstComponent, "Restitution", &restitution);

		AddBox(size, density, offset, isSensor, friction, restitution);
	}
	else if (strcmp(type, "Circle") == 0)
	{
		float radius = scale.x * 0.5f;

		float32 density = 1.0f;
		cJSONExt_GetFloat(firstComponent, "Density", &density);

		b2Vec2 offset = b2Vec2(0.0f, 0.0f);
		cJSONExt_GetFloatArray(firstComponent, "Offset", &offset.x, 2);

		bool isSensor = false;
		cJSONExt_GetBool(firstComponent, "IsSensor", &isSensor);

		float32 friction = 0.7f;
		cJSONExt_GetFloat(firstComponent, "Friction", &friction);

		float32 restitution = 0.0f;
		cJSONExt_GetFloat(firstComponent, "Restitution", &restitution);

		AddCircle(radius, offset, density, isSensor, friction, restitution);
	}
	delete[] type;


	char* othertype = new char[50];
	cJSONExt_GetString(SecondComponent, "Type", othertype, 50);
	std::string stringtype(othertype);

	//if this is true then this is  a joint
	if (stringtype.find("Sprite") == std::string::npos)
	{
		HandleJoints(SecondComponent);

		//if this is a joint then we need a 3rd component to get the material
		cJSON* ThirdComponent = cJSON_GetArrayItem(jComponents, 2);
		char* mat = new char[50];
		cJSONExt_GetString(ThirdComponent, "Material", mat, 50);
		SetMaterial(manager->GetMaterial(mat));
		SetMesh(manager->GetMesh("Box"));
		delete[] mat;
	}
	else //otherwise this is a sprite
	{
		char* mat = new char[50];
		cJSONExt_GetString(SecondComponent, "Material", mat, 50);
		SetMaterial(manager->GetMaterial(mat));
		SetMesh(manager->GetMesh("Box"));
		delete[] mat;
	}
	delete[] othertype;
}

void GameObject::HandleJoints(cJSON* obj)
{
	char* jointType = new char[50];
	cJSONExt_GetString(obj, "Type", jointType, 50);
	std::string stringtype(jointType);
	//check for revolute joints
	if (stringtype.find("Revolute") != std::string::npos)
	{
		bool isMotorEnabled = false;
		cJSONExt_GetBool(obj, "MotorEnabled", &isMotorEnabled);

		float motorSpeed = 0.0f;
		cJSONExt_GetFloat(obj, "MotorSpeed", &motorSpeed);

		float motorTorque = 0.0f;
		cJSONExt_GetFloat(obj, "MotorMaxTorque", &motorTorque);

		CreateRevolute(isMotorEnabled, motorSpeed, motorTorque);
	}


	delete[] jointType;
}
