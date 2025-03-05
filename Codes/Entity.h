#pragma once
#include "Components.h"
#include<memory>
#include<string>

class Entity
{
	friend class EntityManager;

	bool			m_active	= true;
	size_t			m_id		= 0;
	std::string		m_tag		= "Default";

	Entity(size_t id, const std::string& tag);

public:

	CTransform*		cTransform;
	CShape*			cShape;
	CCollision*		cCollision;
	CInput*			cInput;
	CEnemy*			cEnemy;
	CLifespan*		cLifespan;

	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void setActivity(bool newActiveVal);
	void destroy();
};