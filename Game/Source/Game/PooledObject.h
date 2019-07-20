#pragma once
#include "GameObjects/GameObject.h"
#include "Pool.h"

template <class T> class PooledObject
{
protected:
	Pool<T>* m_pPool;
public:
	PooledObject(Pool<T>* pPool)
	{
		assert(pPool != nullptr);
		m_pPool = pPool;
		m_pPool->AddObjectToPool((T)this);
	}

	void ReturnToPool()
	{
		if (m_pPool)
		{
			m_pPool->ReturnObjectToPool((T)this);
		}
	}
};