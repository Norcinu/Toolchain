#ifndef ENTITY_H
#define ENTITY_H

#include <string>

struct Entity_t
{
    bool has_physics;
    bool has_ai;
    float x;
    float y;
    float z
    std::string name;
    std::string graphic_name;

    Entity_t() : 
        has_physics(false),
        has_ai(false),
        x(0),
        y(0),
        z(0),
        name(""),
        graphic_name("") {}

    ~Entity_t() {}
};

#endif
