#include "Entity.h"
#include <cassert>
#include <algorithm>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        //entities.erase(it);
        //entities.pop_back();
    }

    entities.clear();
}

void EntityManager::Add(const Entity::entity_ptr ent)
{
    assert (ent != nullptr);
    entities.push_back(ent);
}

void EntityManager::Remove(const int index)
{
   // assert (index > 0 && index < (int)entities.size());
    
    if (index == 0)
        return;
    
    entities.erase(entities.begin() + index);
}
