#include "Entity.h"

Entity::Entity(size_t id, const std::string& tag)
{
	m_id = id;
	m_tag = tag;
}

bool Entity::isActive() const
{
	return m_active;
}

const std::string& Entity::tag() const
{
	return m_tag;
}

const size_t Entity::id() const
{
	return m_id;
}

void Entity::destroy()
{
	if (this->cTransform != nullptr) delete this->cTransform;
	if (this->cEnemy != nullptr) delete this->cEnemy;
	if (this->cInput != nullptr) delete this->cInput;
	if (this->cLifespan != nullptr) delete this->cLifespan;
	if (this->cShape != nullptr)
	{
		delete this->cShape;
	}
	if (this->cCollision != nullptr) delete this->cCollision;
}

void Entity::setActivity(bool newActiveVal)
{
	m_active = newActiveVal;
}
