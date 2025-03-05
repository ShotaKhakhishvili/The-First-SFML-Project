#include "EntityManager.h"

void EntityManager::destroyEntities(std::vector<Entity*>& entities, bool deallocate)
{
    for (size_t i = 0; i < entities.size(); )
    {
        if (!entities[i]->isActive())
        {
            // Optionally call entity cleanup function
            entities[i]->destroy();
            if (deallocate)
                delete entities[i];

            // Remove the pointer from the vector
            std::swap(entities[i], entities.back());
            entities.pop_back();
        }
        else
        {
            i++;
        }
    }
}



void EntityManager::addEntities()
{
    for (const auto& entity : m_toAdd)
    {
        m_entities.push_back(entity);
        m_entityMap[entity->tag()].push_back(entity);
    }
    m_toAdd.clear();
}

void EntityManager::update()
{
    // Remove and delete inactive entities from the main container.
    destroyEntities(m_entities, true);

    // Now, update the map to remove pointers to deleted entities.
    for (auto& entry : m_entityMap)
    {
        // Remove dangling pointers from the map.
        entry.second.erase(
            std::remove_if(entry.second.begin(), entry.second.end(),
                [this](Entity* e) {
                    return std::find(m_entities.begin(), m_entities.end(), e) == m_entities.end();
                }),
            entry.second.end()
                    );
    }
    addEntities();
}


Entity& EntityManager::toAdd(const std::string& tag)
{
	Entity* newEntity = new Entity(0, tag);

	m_toAdd.insert(newEntity);

	return *newEntity;
}

void EntityManager::toDestroy(Entity* entityToDestroy)
{
    (*entityToDestroy).setActivity(false);
}

const std::vector<Entity*> EntityManager::getEntities() const
{
    return m_entities;
}

const std::vector<Entity*> EntityManager::getEntities(const std::string& tag) const {
    auto it = m_entityMap.find(tag);
    if (it != m_entityMap.end()) {
        return it->second;
    }
    else {
        return std::vector<Entity*>{};  // Return an empty vector if not found.
    }
}
