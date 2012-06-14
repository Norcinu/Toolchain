#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>
#include <vector>

struct Entity
{
    bool has_physics;
    bool has_ai;
    int editor_id; // for editor use only. Do not export!!
    float x;
    float y;
    float z;
    std::string name;
    std::string graphic_name;

    Entity() : 
        has_physics(false),
        has_ai(false),
        editor_id(0),
        x(0),
        y(0),
        z(0),
        name(""),
        graphic_name("") {}

    ~Entity() {}

    typedef std::shared_ptr<Entity> entity_ptr;
};

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    bool Add(const Entity::entity_ptr ent);
    bool Remove(const Entity::entity_ptr ent);

private:
    std::vector<Entity::entity_ptr> entities;
};

typedef std::shared_ptr<EntityManager> EntityManagerPtr;

#endif
