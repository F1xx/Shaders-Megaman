#include "GamePCH.h"
#include "Transformable.h"

Transformable::Transformable(vec3 pos, vec3 rot, vec3 scale)
{
	m_Position = pos;
	m_Rotation = rot;
	m_Scale = scale;
}

Transformable::Transformable(Transform transform)
{
	m_Position = transform.Position;
	m_Rotation = transform.Rotation;
	m_Scale = transform.Scale;
}

Transformable::~Transformable()
{
}
