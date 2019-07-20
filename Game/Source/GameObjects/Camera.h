#pragma once
#include "GamePCH.h"
#include "GameObjects/GameObject.h"

class Camera : public GameObject
{
public:
	Camera(vec3 position, vec3 lookat, float range);
	~Camera();

	void CreateViewMatrix(vec3 up = vec3(0,1,0));
	void CreateProjectionMatrix(float FOV = 45.0f, float nearZ = 0.01f, float aspect = 1.0f );

	//getters&setters
	mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
	void SetProjectionMatrix(mat4 projmat) { m_ProjectionMatrix = projmat; }
	mat4 GetViewMatrix() { return m_ViewMatrix; }
	void SetViewMatrix(mat4 viewmat) { m_ViewMatrix = viewmat; }

	vec3 GetLookAtPosition() { return m_LookAtPosition; }
	void SetLookAtPosition(vec3 lookatpos);
	void SetLookAtTarget(GameObject* pObj, vec3 offset);
	float GetRange() { return m_Range; }
	void SetRange(float range) { m_Range = range; }
	vec3 GetOffset() { return m_Offset; }
	void SetOffset(vec3 offset) { m_Offset = offset; }

	void Update(float deltatime);


protected:
	mat4 m_ProjectionMatrix;
	mat4 m_ViewMatrix;

	GameObject* m_Target;
	vec3 m_Offset;

	float m_Range;
	vec3 m_LookAtPosition;
};