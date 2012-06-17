#include "Entity.h"
#include <cassert>
#include <algorithm>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void 
    EntityManager::Add(const Entity::entity_ptr ent)
{
    assert (ent != nullptr);
    entities.push_back(ent);
}

void EntityManager::Remove(const int index)
{
    assert (index > 0 && index < entities.size());
    
    /*int ctr = 0;
    auto result = std::find_if(entities.begin(), entities.end(), 
        [&ctr, &index] () -> bool {
            if (index == ctr) return true;
            else return false;
        });*/
    
    entities.erase(entities.begin() + index);
}
