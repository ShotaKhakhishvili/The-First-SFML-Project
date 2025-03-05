#pragma once
#include <vector>
#include <set>
#include <map>
#include <thread>
#include "Entity.h"

class EntityManager
{
	std::set<Entity*> m_toAdd;

	std::vector<Entity*> m_entities;
	std::map<std::string, std::vector<Entity*>> m_entityMap;

	size_t entitiesSpawned = 0;

	void destroyEntities(std::vector<Entity*>& entities, bool deallocate);
	void addEntities();

public:

	EntityManager() {};

	void update();

	Entity& toAdd(const std::string& tag);
	void toDestroy(Entity* entityToDestroy);


	const std::vector<Entity*> getEntities() const;
	const std::vector<Entity*> getEntities(const std::string& tag) const;

};