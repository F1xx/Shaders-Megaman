#pragma once

class GameObject;

template <class TYPE> class Pool
{
public:
	Pool() {};

	virtual ~Pool()
	{
		while (!m_Objects.empty())
		{
			delete m_Objects.back();
			m_Objects.pop_back();
		}
	}

	void AddObjectToPool(TYPE obj)
	{
		if (obj != nullptr)
		{
			m_Objects.push_back(obj);
		}
	}

	GameObject* GetObjectFromPool()
	{
		if (m_Objects.empty())
			return nullptr;

		TYPE pObject = m_Objects.back();
		if (pObject != nullptr)
		{
			m_Objects.pop_back();
		}
		return pObject;
	}

	void ReturnObjectToPool(TYPE obj)
	{
		m_Objects.push_back(obj);
	}

protected:
	std::vector<TYPE> m_Objects;
};