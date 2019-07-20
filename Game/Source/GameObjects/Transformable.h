#pragma once

struct Transform
{
	Transform(vec3 pos, vec3 rot, vec3 scale) { Position = pos; Rotation = rot; Scale = scale; }
	Transform() { Position = vec3(0); Rotation = vec3(0); Scale = vec3(1); }

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
};

class Transformable
{
public:
	Transformable(vec3 pos, vec3 rot, vec3 scale);
	Transformable(Transform transform);
	~Transformable();

	vec3 GetPosition() { return m_Position; }
	vec3 GetRotation() { return m_Rotation; }
	vec3 GetScale() { return m_Scale; }

	void SetPosition(vec3 pos) { m_Position = pos; }
	void SetRotation(vec3 rot) { m_Rotation = rot; }
	void SetScale(vec3 scale) { m_Scale = scale; }

protected:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
};