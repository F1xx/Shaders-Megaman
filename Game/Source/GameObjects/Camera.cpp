#include "GamePCH.h"
#include "Camera.h"

Camera::Camera(vec3 position, vec3 lookat, float range)
	: GameObject(nullptr, "Camera", Transform(), nullptr, nullptr)
{
	m_Position = position;
	m_LookAtPosition = lookat;
	m_Range = range;
	m_Offset = vec3(0);
	m_Target = nullptr;
}

Camera::~Camera()
{
}

void Camera::CreateViewMatrix(vec3 up /*= vec3(0,1,0)*/)
{
	m_ViewMatrix.CreateLookAtView(m_Position, up, m_LookAtPosition);
}

void Camera::CreateProjectionMatrix(float FOV /*= 45.0f*/, float nearZ /*= 0.01f*/, float aspect /*= 1.0f */)
{
	m_ProjectionMatrix.CreatePerspectiveVFoV(FOV, aspect, nearZ, m_Range);
}

void Camera::SetLookAtPosition(vec3 lookatpos)
{
	m_LookAtPosition = lookatpos;

	if (m_Target)
	{
		m_Target = nullptr;
	}
}

void Camera::SetLookAtTarget(GameObject* pObj, vec3 offset)
{
	m_LookAtPosition = pObj->GetPosition();
	m_Target = pObj;
	m_Offset = offset;
}

void Camera::Update(float deltatime)
{
	CreateViewMatrix();
	CreateProjectionMatrix();

	if (m_Target)
	{
		m_LookAtPosition = m_Target->GetPosition();
		m_Position = m_Target->GetPosition();
		m_Position += m_Offset;
	}
}
